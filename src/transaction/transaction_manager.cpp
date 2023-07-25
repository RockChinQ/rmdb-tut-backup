/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "transaction_manager.h"
#include "record/rm_file_handle.h"
#include "system/sm_manager.h"

std::unordered_map<txn_id_t, Transaction *> TransactionManager::txn_map = {};

/**
 * @description: 事务的开始方法
 * @return {Transaction*} 开始事务的指针
 * @param {Transaction*} txn 事务指针，空指针代表需要创建新事务，否则开始已有事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
Transaction * TransactionManager::begin(Transaction* txn, LogManager* log_manager) {
    // Todo:
    // 1. 判断传入事务参数是否为空指针
    // 2. 如果为空指针，创建新事务
    // 3. 把开始事务加入到全局事务表中
    // 4. 返回当前事务指针

        // 保护txn_map
    // std::scoped_lock lock(latch_);
    // 1. 判断传入事务参数是否为空指针
    if(txn == nullptr){
        // 2. 如果为空指针，创建新事务
        txn = new Transaction(next_txn_id_);
        next_txn_id_++;
    }
    // 3. 把开始事务加入到全局事务表中
    txn_map[txn->get_transaction_id()] = txn;
    
    // BeginLogRecord *begin_log_rcd = new BeginLogRecord(txn->get_transaction_id());
    // begin_log_rcd->prev_lsn_ = txn->get_prev_lsn();
    // // 这里我让begin log也立即刷入磁盘了
    // txn->set_prev_lsn(log_manager->flush_log_to_disk(begin_log_rcd));
    
    // 不要忘记delete
    // delete begin_log_rcd;

    // 4. 返回当前事务指针
    return txn;
    
    //return nullptr;
}

/**
 * @description: 事务的提交方法
 * @param {Transaction*} txn 需要提交的事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
void TransactionManager::commit(Transaction* txn, LogManager* log_manager) {
    // Todo:
    // 1. 如果存在未提交的写操作，提交所有的写操作
    // 2. 释放所有锁
    // 3. 释放事务相关资源，eg.锁集
    // 4. 把事务日志刷入磁盘中
    // 5. 更新事务状态

    txn->set_state(TransactionState::COMMITTED);

}

/**
 * @description: 事务的终止（回滚）方法
 * @param {Transaction *} txn 需要回滚的事务
 * @param {LogManager} *log_manager 日志管理器指针
 */
void TransactionManager::abort(Transaction * txn, LogManager *log_manager) {
    // Todo:
    // 1. 回滚所有写操作
    // 2. 释放所有锁
    // 3. 清空事务相关资源，eg.锁集
    // 4. 把事务日志刷入磁盘中
    // 5. 更新事务状态
    
    // 1. 回滚该事务所有的写操作
    auto table_write_set = txn->get_table_write_set();
    Context context(lock_manager_,log_manager,txn);
    while(!table_write_set->empty()){
        auto write_rcd = table_write_set->back();
        auto &rm_file_hdl = sm_manager_->fhs_.at(write_rcd->GetTableName());
        switch(write_rcd->GetWriteType()){
            case WType::INSERT_TUPLE:{
                rm_file_hdl->delete_record(write_rcd->GetRid(),&context);
                break;
            }
            case WType::DELETE_TUPLE:{
                rm_file_hdl->insert_record(write_rcd->GetRecord().data,&context);
                break;
            }
            case WType::UPDATE_TUPLE:{
                rm_file_hdl->update_record(write_rcd->GetRid(),write_rcd->GetRecord().data,&context);
                break;
            }
        }
        
        table_write_set->pop_back();

        delete write_rcd;
    }

    table_write_set->clear();

    auto index_write_set = txn->get_index_write_set();
    while(!index_write_set->empty()){
        auto index_write_rcd = index_write_set->back();
        std::string table_name = index_write_rcd->GetTableName();
        auto tabs = sm_manager_->db_.get_table(table_name);
        auto indexes = sm_manager_->db_.get_table(table_name).indexes;
        switch(index_write_rcd->GetWriteType()){
            case WType::INSERT_TUPLE:{
                for(size_t i = 0; i < indexes.size(); ++i) {
                    auto& index = indexes[i];
                    auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(table_name, index.cols)).get();
                    ih->delete_entry(index_write_rcd->GetKey(),txn);
                    
                }
                break;
            }
            case WType::DELETE_TUPLE:{
                for(size_t i = 0; i < indexes.size(); ++i) {
                    auto& index = indexes[i];
                    auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(table_name, index.cols)).get();
                    
                    ih->insert_entry(index_write_rcd->GetKey(),index_write_rcd->GetRid(),txn);
                    
                }
                break;
            }
        }
        index_write_set->pop_back();

        delete index_write_rcd;
    }

    index_write_set->clear();

    // 5. 更新事务状态
    txn->set_state(TransactionState::ABORTED);

}