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
#include "index/ix.h"
#include "system/sm.h"

class UpdateExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    TabMeta tab_;
    std::vector<Condition> conds_;
    RmFileHandle *fh_;
    std::vector<Rid> rids_;
    // std::string tab_name_;
    std::vector<SetClause> set_clauses_;
    // SmManager *sm_manager_;

   public:
    UpdateExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<SetClause> set_clauses,
                   std::vector<Condition> conds, std::vector<Rid> rids, Context *context) {
        sm_manager_ = sm_manager;
        tab_name_ = tab_name;
        set_clauses_ = set_clauses;
        tab_ = sm_manager_->db_.get_table(tab_name);
        fh_ = sm_manager_->fhs_.at(tab_name).get();
        conds_ = conds;
        rids_ = rids;
        context_ = context;

        std::cout<<"conds_.size(): "<<conds_.size()<<std::endl;
    }

    // size_t tupleLen() const override { return tab_.tuple_len; }

    std::string getType() override { return "UpdateExecutor"; }

    const std::vector<ColMeta> &cols() const override { return tab_.cols; }

    std::unique_ptr<RmRecord> Next() override {

        for (auto &rid : rids_) {
            std::cout<<"UpdateExecutor Next rid: "<<rid.page_no<<" "<<rid.slot_no<<std::endl;
            auto record = fh_->get_record(rid, context_);

            if (!check_conds(conds_, *record)) {
                continue;
            }

            std::cout<<"UpdateExecutor setting"<<std::endl;
            // 设置每个字段
            for (auto &set_clause : set_clauses_) {
                std::cout<<"UpdateExecutor setting: "<<set_clause.lhs.col_name<<std::endl;
                auto col = set_clause.lhs;
                auto val = set_clause.rhs;

                auto col_meta = sm_manager_->db_.get_table(set_clause.lhs.tab_name).get_col(col.col_name)[0];

                int offset = col_meta.offset;
                int len = col_meta.len;

                int rlen = 0;
                if (val.type == TYPE_INT) {
                    std::cout<<"UpdateExecutor setting: "<<val.int_val<<std::endl;
                    rlen = sizeof(int);
                } else if (val.type == TYPE_FLOAT) {
                    std::cout<<"UpdateExecutor setting: "<<val.float_val<<std::endl;
                    rlen = sizeof(float);
                } else if (val.type == TYPE_STRING) {
                    std::cout<<"UpdateExecutor setting: "<<val.str_val<<std::endl;
                    rlen = val.str_val.size();
                }

                val.init_raw(rlen);

                record->set_column_value(offset, len, val.raw->data);
            }

            fh_->update_record(rid, record.get()->data, context_);
        }

        return nullptr;
    }

    Rid &rid() override { return _abstract_rid; }
};