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

class DeleteExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    TabMeta tab_;                   // 表的元数据
    std::vector<Condition> conds_;  // delete的条件
    RmFileHandle *fh_;              // 表的数据文件句柄
    std::vector<Rid> rids_;         // 需要删除的记录的位置
    std::string tab_name_;          // 表名称
    SmManager *sm_manager_;

   public:
    DeleteExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<Condition> conds,
                   std::vector<Rid> rids, Context *context) {
        sm_manager_ = sm_manager;
        tab_name_ = tab_name;
        tab_ = sm_manager_->db_.get_table(tab_name);
        fh_ = sm_manager_->fhs_.at(tab_name).get();
        conds_ = conds;
        rids_ = rids;
        context_ = context;

        if(context_ != nullptr) {
            context_->lock_mgr_->lock_IX_on_table(context_->txn_, fh_->GetFd());
        }
    }

    std::string getType() override { return "DeleteExecutor"; }

    const std::vector<ColMeta> &cols() const override { return tab_.cols; }

    std::unique_ptr<RmRecord> Next() override {
        
        // if(context_ != nullptr) {
        //     context_->lock_mgr_->lock_IX_on_table(context_->txn_, fh_->GetFd());
        // }

        for (auto &rid : rids_) {

            auto record = fh_->get_record(rid, context_);

            RmRecord delete_rcd(record->size);
            memcpy(delete_rcd.data,record->data,record->size);
            // 删除index
            // 这里与index插入是相似的，都是对每一个的index，得到对应col的key，调用delete_entry(key,context_->txn_);        
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

            // 删除记录
            fh_->delete_record(rid, context_);

            TableWriteRecord *write_record = new TableWriteRecord(WType::DELETE_TUPLE,tab_name_,rid,delete_rcd);
            context_->txn_->append_table_write_record(write_record);

        }

        return nullptr;
    }

    Rid &rid() override { return _abstract_rid; }
};