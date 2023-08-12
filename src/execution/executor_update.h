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

        if(context_ != nullptr) {
            context_->lock_mgr_->lock_IX_on_table(context_->txn_, fh_->GetFd());
        }
    }

    // size_t tupleLen() const override { return tab_.tuple_len; }

    std::string getType() override { return "UpdateExecutor"; }

    const std::vector<ColMeta> &cols() const override { return tab_.cols; }

    std::unique_ptr<RmRecord> Next() override {

        // if(context_ != nullptr) {
        //     context_->lock_mgr_->lock_IX_on_table(context_->txn_, fh_->GetFd());
        // }

        for (auto &rid : rids_) {
            auto record = fh_->get_record(rid, context_);
            auto new_record = std::make_unique<RmRecord>(*record);
            if (!check_conds(conds_, *record)) {
                continue;
            }

            // 删除所有的index
            for(size_t i = 0; i < tab_.indexes.size(); ++i) {
                auto& index = tab_.indexes[i];
                auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index.cols)).get();
                char key[index.col_tot_len];
                int offset = 0;
                for(size_t i = 0; i < index.col_num; ++i) {
                    memcpy(key + offset, record->data + index.cols[i].offset, index.cols[i].len);
                    offset += index.cols[i].len;
                }
                ih->delete_entry(key, context_->txn_);

                IndexWriteRecord *index_rcd = new IndexWriteRecord(WType::DELETE_TUPLE,tab_name_,rid,key,index.col_tot_len);
                context_->txn_->append_index_write_record(index_rcd);

            }

            // 设置每个字段
            for (auto &set_clause : set_clauses_) {
                auto col = set_clause.lhs;
                auto val = set_clause.rhs;

                auto col_meta = sm_manager_->db_.get_table(set_clause.lhs.tab_name).get_col(col.col_name)[0];

                int offset = col_meta.offset;
                int len = col_meta.len;

            //     // int rlen = 0;
            //     // if (val.type == TYPE_INT) {
            //     //     rlen = sizeof(int);
            //     // } else if (val.type == TYPE_FLOAT) {
            //     //     rlen = sizeof(float);
            //     // } else if (val.type == TYPE_STRING) {
            //     //     rlen = val.str_val.size();
            //     // } else if (val.type == TYPE_DATETIME) {
            //     //     rlen = sizeof(uint64_t);
            //     // } else if (val.type == TYPE_BIGINT) {
            //     //     rlen = sizeof(int64_t);
            //     // } else {
            //     //     throw InvalidTypeError();
            //     // }

                Value *new_val = insert_compatible(col_meta.type, val);

                new_val->init_raw(col_meta.len);

                new_record->set_column_value(offset, len, new_val->raw->data);
            }

            fh_->update_record(rid, new_record.get()->data, context_);

            TableWriteRecord *write_rcd = new TableWriteRecord(WType::UPDATE_TUPLE,tab_name_,rid,*record);
            context_->txn_->append_table_write_record(write_rcd);

            // // 更新record file
            // char new_record[fh_->get_file_hdr().record_size];
            // memcpy(new_record, record->data, fh_->get_file_hdr().record_size);
            // for(auto &set_clause: set_clauses_) {
            //     auto lhs_col = tab_.get_col(set_clause.lhs.col_name);
            //     // 在内存中修改
            //     memcpy(new_record + lhs_col->offset, set_clause.rhs.raw->data, lhs_col->len);
            // }
            //             // 对磁盘修改
            // fh_->update_record(rid, new_record, context_);

            try {
                // 将rid插入在内存中更新后的新的record的cols对应key的index
                for(size_t i = 0; i < tab_.indexes.size(); ++i) {
                    auto& index = tab_.indexes[i];
                    auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index.cols)).get();
                    char key[index.col_tot_len];
                    int offset = 0;
                    for(size_t i = 0; i < index.col_num; ++i) {
                        memcpy(key + offset, new_record->data + index.cols[i].offset, index.cols[i].len);
                        offset += index.cols[i].len;
                    }
                    ih->insert_entry(key,rid,context_->txn_);
                    
                    IndexWriteRecord *index_rcd = new IndexWriteRecord(WType::INSERT_TUPLE,tab_name_,rid,key,index.col_tot_len);
                    context_->txn_->append_index_write_record(index_rcd);

                }
            }catch(InternalError &error) {
                // 1. 恢复record
                fh_->update_record(rid, record->data, context_);
                // 恢复索引
                // 2. 恢复所有的index
                for(size_t i = 0; i < tab_.indexes.size(); ++i) {
                    auto& index = tab_.indexes[i];
                    auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index.cols)).get();
                    char key[index.col_tot_len];
                    int offset = 0;
                    for(size_t i = 0; i < index.col_num; ++i) {
                        memcpy(key + offset, record->data + index.cols[i].offset, index.cols[i].len);
                        offset += index.cols[i].len;
                    }
                    ih->insert_entry(key, rid, context_->txn_);
                }

                // 3. 继续抛出异常
                throw InternalError("Non-unique index!");
            }

        }

        return nullptr;
    }

    Rid &rid() override { return _abstract_rid; }
};