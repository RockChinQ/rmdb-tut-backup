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

class SeqScanExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    // std::string tab_name_;              // 表的名称
    std::vector<Condition> conds_;      // scan的条件
    RmFileHandle *fh_;                  // 表的数据文件句柄
    std::vector<ColMeta> cols_;         // scan后生成的记录的字段
    size_t len_;                        // scan后生成的每条记录的长度
    std::vector<Condition> fed_conds_;  // 同conds_，两个字段相同

    Rid rid_;
    std::unique_ptr<RecScan> scan_;     // table_iterator

    // SmManager *sm_manager_;
    bool isend;

   public:
    SeqScanExecutor(SmManager *sm_manager, std::string tab_name, std::vector<Condition> conds, Context *context) {

        sm_manager_ = sm_manager;
        tab_name_ = std::move(tab_name);
        conds_ = std::move(conds);
        TabMeta &tab = sm_manager_->db_.get_table(tab_name_);
        fh_ = sm_manager_->fhs_.at(tab_name_).get();
        cols_ = tab.cols;
        len_ = cols_.back().offset + cols_.back().len;
        isend = false;

        context_ = context;

        fed_conds_ = conds_;

        RmScan *scan = new RmScan(fh_);
        scan_ = std::unique_ptr<RecScan>(scan);

        if(context != nullptr) {
            context->lock_mgr_->lock_shared_on_table(context->txn_, fh_->GetFd());
        }
    }

    size_t tupleLen() const override { return len_; }

    std::string getType() override { return "SeqScanExecutor"; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    void beginTuple() override {
        // 为scan_赋值
        // RmScan *scan = new RmScan(fh_);
        // scan_ = std::unique_ptr<RecScan>(scan);
        scan_->begin();
        auto rec = scan_.get()->rid();
        nextTuple();

        isend = false;
    }

    void nextTuple() override {
        // 先检查此条记录是否满足所有条件
        // 再next下一条
        // 返回的是此条！！！！！！！！！！！！！！！！！
        scan_->next();
        while (!scan_->is_end()) {
            auto rec = scan_.get()->rid();
            auto record = fh_->get_record(rec, context_);

            // 检查所有条件
            bool flag = true;

            for (auto &cond : conds_) {
                if (!check_cond(cond, *record)) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                rid_ = rec;
                // scan_->next();
                return;
            }
            scan_->next();
        }
        isend = true;
    }

    bool is_end() const override {
    
        return scan_->is_end();
        
    }

    std::unique_ptr<RmRecord> Next() override {
        // nextTuple();
        // if (scan_->is_end()) {
        //     std::cout<<"executor_seq_scan Next is_end"<<std::endl;
        //     return nullptr;
        // }
        std::cout<<"getting next from seq scan"<<std::endl;
        auto rec = rid();

        auto record = fh_->get_record(rec, context_);

        return record;
    }

    Rid &rid() override { return rid_; }

};