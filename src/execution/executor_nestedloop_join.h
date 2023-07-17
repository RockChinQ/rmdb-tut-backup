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

class NestedLoopJoinExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    std::unique_ptr<AbstractExecutor> left_;    // 左儿子节点（需要join的表）
    std::unique_ptr<AbstractExecutor> right_;   // 右儿子节点（需要join的表）
    size_t len_;                                // join后获得的每条记录的长度
    std::vector<ColMeta> cols_;                 // join后获得的记录的字段

    std::vector<Condition> fed_conds_;          // join条件
    bool isend;

   public:
    NestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right, 
                            std::vector<Condition> conds) {
        left_ = std::move(left);
        right_ = std::move(right);
        len_ = left_->tupleLen() + right_->tupleLen();
        cols_ = left_->cols();
        auto right_cols = right_->cols();
        for (auto &col : right_cols) {
            col.offset += left_->tupleLen();
        }

        cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
        isend = false;
        fed_conds_ = std::move(conds);

        // 将left转换成ConditionDependedExecutor
        // auto cde_left = std::make_unique<ConditionDependedExecutor>();

        // sm_manager_ = cde_left->get_sm_manager();

        // std::cout<<"*** is sm_manager_ null?"<<(sm_manager_ == nullptr)<<std::endl;

    }

    std::string getType() override { return "NestedLoopJoinExecutor"; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    void beginTuple() override {
        left_->beginTuple();
        right_->beginTuple();

        // left_->nextTuple();
        // right_->nextTuple();
    }

    void nextTuple() override {
        // std::cout<<"left cols tab_name: "<<left_.get()->cols()[0].tab_name<<std::endl;
        // for (;!left_->is_end();) {
        //     std::cout<<"left rid: "<<left_->rid().page_no<<" "<<left_->rid().slot_no<<std::endl;
        //     std::cout<<"right is_end: "<<right_->is_end()<<std::endl;
        //     for (;!right_->is_end();) {
        //         std::cout<<"right rid: "<<right_->rid().page_no<<" "<<right_->rid().slot_no<<std::endl;

        //         auto lrec = left_->Next();
        //         auto rrec = right_->Next();

        //         // 伪装一个cond出来
        //         // which 左边是左表的列，右边是右表的列值
        //         std::vector<Condition> conds;
        //         for (auto &cond : fed_conds_) {
        //             Condition new_cond;
                    
        //             new_cond.lhs_col = cond.lhs_col;
        //             new_cond.is_rhs_val = true;

        //             if (cond.is_rhs_val) {
        //                 new_cond.rhs_val = cond.rhs_val;
        //             } else {
        //                 new_cond.rhs_val = get_record_value(*(rrec.get()), cond.rhs_col);
        //             }

        //             conds.push_back(new_cond);
        //         }

        //         if (check_conds(conds, *lrec.get())) {
        //             // 符合条件，返回
        //             std::cout<<"return l("<<left_->rid().page_no<<" "<<left_->rid().slot_no<<") r("<<right_->rid().page_no<<" "<<right_->rid().slot_no<<")"<<std::endl;
                    
        //             right_->nextTuple();
        //             return;
        //         }

        //         right_->nextTuple();
        //     }
        //     right_->beginTuple();
        //     left_->nextTuple();
        // }
        // isend = true;
        // right_->nextTuple();
        // if (right_->is_end()) {
        //     left_->nextTuple();
        //     right_->beginTuple();
        // }
        std::cout<<"NestedLoopJoinExecutor nextTuple"<<std::endl;
        while(true){
            left_->nextTuple();

            if (left_->is_end()) {
                right_->nextTuple();
                left_->beginTuple();
                if (right_->is_end()) {
                    isend = true;
                    return;
                }
            }

            // std::cout<<"left rid: "<<left_->rid().page_no<<" "<<left_->rid().slot_no<<std::endl;
            std::cout<<"nlje sub next"<<std::endl;

            auto lrec = left_->Next();
            auto rrec = right_->Next();

            std::cout<<"left rid("<<left_->rid().page_no<<" "<<left_->rid().slot_no<<") right rid("<<right_->rid().page_no<<" "<<right_->rid().slot_no<<")"<<std::endl;

            // 伪装一个cond出来
            // which 左边是左表的列，右边是右表的列值
            // std::vector<Condition> conds;
            // for (auto &cond : fed_conds_) {
            //     std::cout<<"making fake cond"<<std::endl;
            //     Condition new_cond;
                
            //     new_cond.lhs_col = cond.lhs_col;
            //     new_cond.is_rhs_val = true;

            //     if (cond.is_rhs_val) {
            //         new_cond.rhs_val = cond.rhs_val;
            //     } else {
            //         std::cout<<"get_record_value"<<std::endl;
            //         new_cond.rhs_val = get_record_value(*(rrec.get()), cond.rhs_col);
            //         std::cout<<"get_record_value end"<<std::endl;
            //     }

            //     conds.push_back(new_cond);
            //     std::cout<<"fake cond made;"<<std::endl;
            // }
            // std::cout<<"fake cond made, check conds"<<std::endl;

            bool flag = true;

            for (auto &cond : fed_conds_){

                std::cout<<"checking cond:"<<cond.lhs_col.col_name<<" "<<cond.op<<" "<<cond.rhs_col.col_name<<" "<<cond.is_rhs_val<<std::endl;
                // 从左表中查出此字段信息
                int left_off=0, left_len = 0;
                ColType left_type;

                auto col_meta = left_.get()->cols();
                for (auto &lcol : col_meta){
                    std::cout<<"***** matching left col:"<<lcol.tab_name<<" "<<lcol.name<<" "<<cond.lhs_col.col_name<<std::endl;
                    if (lcol.name.compare(cond.lhs_col.col_name)==0){
                        left_off = lcol.offset;
                        left_len = lcol.len;
                        left_type = lcol.type;
                        std::cout<<"left col found: off:"<<left_off<<" len:"<<left_len<<" type:"<<left_type<<std::endl;
                    }
                }

                int right_off=0, right_len = 0;
                ColType right_type;

                col_meta = right_.get()->cols();
                for (auto &rcol : col_meta){
                    if (rcol.name.compare(cond.rhs_col.col_name)==0){
                        right_off = rcol.offset;
                        right_len = rcol.len;
                        right_type = rcol.type;
                        std::cout<<"right col found: off:"<<right_off<<" len:"<<right_len<<" type:"<<right_type<<std::endl;
                    }
                }

                Value left_val = get_record_value(*lrec.get(), left_off, left_len, left_type);
                Value right_val = get_record_value(*rrec.get(), right_off, right_len, right_type);

                if (!check_cond(left_val, right_val, cond)){
                    flag = false;
                    break;
                }

            }

            if (flag) {
                // 符合条件，返回
                std::cout<<"return l("<<left_->rid().page_no<<" "<<left_->rid().slot_no<<") r("<<right_->rid().page_no<<" "<<right_->rid().slot_no<<")"<<std::endl;
                
                return;
            }
        }
    }

    bool is_end() const override {
        bool end = right_->is_end();
        std::cout<<"NestedLoopJoinExecutor is_end: "<<end<<std::endl;
        return end;
    }

    std::unique_ptr<RmRecord> Next() override {


        RmRecord new_rec(len_);

        if (is_end()) {
            return nullptr;
        }

        std::cout<<"===============NEXT"<<std::endl;
        std::cout<<"===============L("<<left_->rid().page_no<<" "<<left_->rid().slot_no<<") R("<<right_->rid().page_no<<" "<<right_->rid().slot_no<<")"<<std::endl;

        auto lrec = left_->Next();
        auto rrec = right_->Next();

        for (auto &col : cols_) {
            std::cout<<"NestedLoopJoinExecutor Next col: "<<col.name<<" tab_name: "<<col.tab_name<<std::endl;

            // 将左右转换成ConditionDependedExecutor


            if (col.offset < left_->tupleLen()) {
                // 左表
                std::cout<<"left"<<std::endl;
                // 查找此列在左表中的位置
                auto col_meta = left_.get()->cols();
                for (auto &c : col_meta) {
                    if (c.name.compare(col.name) == 0) {

                        std::cout<<"## set res col val: col.off: "<<col.offset<<" col.len: "<<col.len<<" lrec.off: "<<c.offset<<" lrec.len: "<<c.len<<" col.name: "<<col.name<<std::endl;
                        new_rec.set_column_value(
                            col.offset,
                            col.len,
                            lrec->get_column_value(
                                c.offset,
                                c.len
                            )
                        );
                        break;
                    }
                }

            } else {
                // 右表
                std::cout<<"right"<<std::endl;
                // 查找此列在右表中的位置
                auto col_meta = right_.get()->cols();
                for (auto &c : col_meta) {
                    if (c.name.compare(col.name) == 0) {

                        std::cout<<"## set res col val: col.off: "<<col.offset<<" col.len: "<<col.len<<" rrec.off: "<<c.offset<<" rrec.len: "<<c.len<<" col.name: "<<col.name<<std::endl;
                        new_rec.set_column_value(
                            col.offset,
                            col.len,
                            rrec->get_column_value(
                                c.offset,
                                c.len
                            )
                        );
                        break;
                    }
                }
            }
        }

        auto unique_ptr_new_rec = std::make_unique<RmRecord>(new_rec);

        std::cout<<"===============NEXT END"<<std::endl;
        std::cout<<"is unique_ptr_new_rec null: "<<(unique_ptr_new_rec == nullptr)<<std::endl;

        return unique_ptr_new_rec;
    }

    Rid &rid() override { return _abstract_rid; }
};