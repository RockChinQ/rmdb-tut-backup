/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "exexution_conddep.h"
#include "index/ix.h"
#include "system/sm.h"

class IndexScanExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    // std::string tab_name_;                      // 表名称
    TabMeta tab_;                               // 表的元数据
    std::vector<Condition> conds_;              // 扫描条件
    RmFileHandle *fh_;                          // 表的数据文件句柄
    std::vector<ColMeta> cols_;                 // 需要读取的字段
    size_t len_;                                // 选取出来的一条记录的长度
    std::vector<Condition> fed_conds_;          // 扫描条件，和conds_字段相同

    std::vector<std::string> index_col_names_;  // index scan涉及到的索引包含的字段
    IndexMeta index_meta_;                      // index scan涉及到的索引元数据

    IxIndexHandle *ixh_;                        // 索引句柄

    Rid rid_;
    std::unique_ptr<RecScan> scan_;

    // SmManager *sm_manager_;

   public:
    IndexScanExecutor(SmManager *sm_manager, std::string tab_name, std::vector<Condition> conds, std::vector<std::string> index_col_names, IndexMeta index_meta, Context *context) {

        std::cout<<"IndexScanExecutor begin"<<std::endl;

        sm_manager_ = sm_manager;
        context_ = context;
        tab_name_ = std::move(tab_name);
        tab_ = sm_manager_->db_.get_table(tab_name_);
        conds_ = std::move(conds);
        // index_no_ = index_no;
        index_col_names_ = index_col_names; 
        //index_meta_ = *(tab_.get_index_meta(index_col_names_));
        index_meta_ = index_meta;
        std::cout<<"IndexScanExecutor index_meta_:"<<std::endl;

        fh_ = sm_manager_->fhs_.at(tab_name_).get();

        std::cout<<"IndexScanExecutor fh_:"<<std::endl;

        std::cout<<"index name1:"<<sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_col_names_)<<std::endl;
        std::cout<<"index name2:"<<sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_meta_.cols)<<std::endl;

        ixh_ = sm_manager_->ihs_.at(
            sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_meta_.cols)
        ).get();

        std::cout<<"1"<<std::endl;
        std::cout<<"IndexScanExecutor index_name:"<<sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_col_names_)<<std::endl;

        cols_ = tab_.cols;
        len_ = cols_.back().offset + cols_.back().len;
        std::map<CompOp, CompOp> swap_op = {
            {OP_EQ, OP_EQ}, {OP_NE, OP_NE}, {OP_LT, OP_GT}, {OP_GT, OP_LT}, {OP_LE, OP_GE}, {OP_GE, OP_LE},
        };

        for (auto &cond : conds_) {
            if (cond.lhs_col.tab_name != tab_name_) {
                // lhs is on other table, now rhs must be on this table
                assert(!cond.is_rhs_val && cond.rhs_col.tab_name == tab_name_);
                // swap lhs and rhs
                std::swap(cond.lhs_col, cond.rhs_col);
                cond.op = swap_op.at(cond.op);
            }
        }
        fed_conds_ = conds_;

        if(context_ != nullptr) {
            context_->lock_mgr_->lock_shared_on_table(context_->txn_, fh_->GetFd());
        }

        std::cout<<"IndexScanExecutor end"<<std::endl;
    }

    std::string getType() override { return "IndexScanExecutor"; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    size_t tupleLen() const override { return len_; }

    void beginTuple() override {

        // if(context_ != nullptr) {
        //     context_->lock_mgr_->lock_shared_on_table(context_->txn_, fh_->GetFd());
        // }

        std::cout<<"IndexScanExecutor beginTuple"<<std::endl;

        // 确定上下界
        RmRecord lower_rec(index_meta_.col_tot_len), upper_rec(index_meta_.col_tot_len);

        size_t off = 0;

        for (auto col : index_meta_.cols) {

            std::cout<<"IndexScanExecutor col.name:"<<col.name<<std::endl;

            Value maxv, minv;

            int col_len = 0;
            switch (col.type) {
                case TYPE_INT: {
                    maxv.set_int(INT32_MAX);
                    minv.set_int(INT32_MIN);
                    break;
                }
                case TYPE_FLOAT: {
                    maxv.set_float(__FLT_MAX__);
                    minv.set_float(-__FLT_MAX__);
                    break;
                }
                case TYPE_STRING:{
                    maxv.set_string(std::string(col.len, 255));
                    minv.set_string(std::string(col.len, 0));
                    break;
                }

                case TYPE_DATETIME : {
                    maxv.set_datetime(std::string("9999-12-31 23:59:59")); 
                    minv.set_datetime(std::string("1000-01-01 00:00:00")); 
                    break;
                }

                case TYPE_BIGINT : {
                    throw RMDBError("在index_scan中还没实现type bigint");
                }

                // TODO: BIGINT 和 DATETIME
                default:{
                    throw InvalidTypeError();
                }
            }

            // 判断cond
            for (auto cond : conds_){
                if (cond.lhs_col.col_name == col.name && cond.is_rhs_val){
                    std::cout<<"IndexScanExecutor cond.lhs_col.col_name:"<<cond.lhs_col.col_name<<std::endl;
                    switch (cond.op){
                        case OP_EQ:{
                            if (check_cond(cond.rhs_val, minv, OP_GT)) {
                                minv = cond.rhs_val;
                            }
                            if (check_cond(cond.rhs_val, maxv, OP_LT)) {
                                maxv = cond.rhs_val;
                            }
                            break;
                        }
                        case OP_GT: {}
                        case OP_GE: {
                            if (check_cond(cond.rhs_val, minv, OP_GT)) {
                                minv = cond.rhs_val;
                            }
                            break;
                        }
                        case OP_LT: {}
                        case OP_LE: {
                            if (check_cond(cond.rhs_val, maxv, OP_LT)) {
                                maxv = cond.rhs_val;
                            }
                            break;
                        }
                        case OP_NE: {
                            break;
                        }
                        default:{
                            throw InternalError("Unexpected CompOp field type");
                        }
                    }
                    std::cout<<"IndexScanExecutor cond.lhs_col.col_name:"<<cond.lhs_col.col_name<<" done"<<std::endl;
                    break;
                }
            }

            maxv.init_raw(col.len);
            minv.init_raw(col.len);

            assert(check_cond(minv, maxv, OP_LE));

            memcpy(upper_rec.data + off, maxv.raw->data, col.len);
            memcpy(lower_rec.data + off, minv.raw->data, col.len);
            off += col.len;

            std::cout<<"IndexScanExecutor done one loop"<<std::endl;

        }

        std::cout<<"IndexScanExecutor making lower and upper"<<std::endl;

        auto lower_id = ixh_->lower_bound(lower_rec.data);
        auto upper_id = ixh_->upper_bound(upper_rec.data);

        std::cout<<"lower_id: ("<<lower_id.page_no<<", "<<lower_id.slot_no<<")"<<std::endl;
        std::cout<<"upper_id: ("<<upper_id.page_no<<", "<<upper_id.slot_no<<")"<<std::endl;

        scan_ = std::make_unique<IxScan>(ixh_, lower_id, upper_id, sm_manager_->get_bpm());

        std::cout<<"scan_->is_end() "<<scan_->is_end()<<std::endl;

        while(!scan_->is_end()) {
            rid_ = scan_->rid();
            std::unique_ptr<RmRecord> rec = fh_->get_record(rid_, context_);
            bool flag = true;

            for (auto cond : conds_){
                auto col = *get_col(cols_, cond.lhs_col);
                auto val = get_record_value(rec, col);

                if (cond.is_rhs_val && !check_cond(val, cond.rhs_val, cond.op)){
                    flag = false;
                    break;
                }
            }

            if (flag){
                std::cout<<"set rid in the begin: ("<<rid_.page_no<<","<<rid_.slot_no<<")"<<std::endl;
                break;
            } else {
                scan_->next();
            }
        }
    }

    void nextTuple() override {
        std::cout<<"IndexScanExecutor nextTuple"<<std::endl;
        assert(!is_end());
        scan_->next();

        while(!scan_->is_end()){
            rid_ = scan_->rid();
            std::unique_ptr<RmRecord> rec = fh_->get_record(rid_, context_);
            bool flag = true;

            for (auto cond : conds_){
                auto col = *get_col(cols_, cond.lhs_col);
                auto val = get_record_value(rec, col);

                if (cond.is_rhs_val && !check_cond(val, cond.rhs_val, cond.op)){
                    flag = false;
                    break;
                }
            }

            if (flag){
                break;
            } else {
                scan_->next();
            }
        }
        std::cout<<"IndexScanExecutor nextTuple done"<<std::endl;
    }

    std::unique_ptr<RmRecord> Next() override {
        std::cout<<"IndexScanExecutor Next"<<std::endl;
        assert(!is_end());
        return fh_->get_record(rid_, context_);
    }

    bool is_end() const override { return scan_->is_end(); }

    Rid &rid() override { return rid_; }
};