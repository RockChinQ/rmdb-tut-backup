/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "lock_manager.h"

/**
 * @description: 申请行级共享锁
 * @return {bool} 加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {Rid&} rid 加锁的目标记录ID 记录所在的表的fd
 * @param {int} tab_fd
 */
bool LockManager::lock_shared_on_record(Transaction* txn, const Rid& rid, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want S R"<<std::endl;
    
    std::scoped_lock lock{latch_};
    if(!check_lock(txn)){   // 2PL
        return false;
    }
    LockDataId lock_id = LockDataId(tab_fd, rid, LockDataType::RECORD);    //锁请求对象

    if(!lock_table_.count(lock_id)) {     // 放入全局锁表
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }

    LockRequest request(txn->get_transaction_id(), LockMode::SHARED);   //lock request
    LockRequestQueue &request_q = lock_table_[lock_id];

    for(auto &it : request_q.request_queue_) {      
        if(it.txn_id_ == txn->get_transaction_id()) {       // 事务已加锁
            return true;
        }
    }
        // 申请锁
    if(GroupLockMode::S == request_q.group_lock_mode_  || GroupLockMode::NON_LOCK == request_q.group_lock_mode_) {
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);
        request.granted_ = true;
        request_q.group_lock_mode_ = GroupLockMode::S;
        request_q.request_queue_.emplace_back(request);
    } else {    //abort
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }

    return true;
}

/**
 * @description: 申请行级排他锁
 * @return {bool} 加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {Rid&} rid 加锁的目标记录ID
 * @param {int} tab_fd 记录所在的表的fd
 */
bool LockManager::lock_exclusive_on_record(Transaction* txn, const Rid& rid, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want X R"<<std::endl;

    std::scoped_lock lock{latch_};
    if(!check_lock(txn)){
        return false;
    }
    // 锁请求对象
    LockDataId lock_id = LockDataId(tab_fd, rid, LockDataType::RECORD);

    if(!lock_table_.count(lock_id)) {     //放入全局锁表
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }
    // lock request
    LockRequest request(txn->get_transaction_id(), LockMode::EXLUCSIVE);
    LockRequestQueue &request_q = lock_table_[lock_id];

    for(auto &it : request_q.request_queue_) {  // 队列中有该事务
        if(it.txn_id_ == txn->get_transaction_id()) {
            if(it.lock_mode_ == LockMode::EXLUCSIVE) {
                return true;    // 该事务已加X锁
            }else {
                // 该事务已加S锁                                    
                if(request_q.group_lock_mode_ == GroupLockMode::S && request_q.request_queue_.size() == 1) {
                    it.lock_mode_ = LockMode::EXLUCSIVE;            // 没有其他锁
                    request_q.group_lock_mode_ = GroupLockMode::X;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 申请X锁
    if(request_q.group_lock_mode_ == GroupLockMode::NON_LOCK) {     // 没有任何其他锁
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);
        request.granted_ = true;
        request_q.group_lock_mode_ = GroupLockMode::X;
        request_q.request_queue_.emplace_back(request);
    }else {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }
    return true;
}

/**
 * @description: 申请表级读锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_shared_on_table(Transaction* txn, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want S T"<<std::endl;
   
    std::scoped_lock lock{latch_};
    if(!check_lock(txn)){
        return false;
    }

    // 锁请求对象
    LockDataId lock_id = LockDataId(tab_fd, LockDataType::TABLE);
    
    if(!lock_table_.count(lock_id)) {  //全局
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }

    //lock request
    LockRequest request(txn->get_transaction_id(), LockMode::SHARED);
    LockRequestQueue &request_q = lock_table_[lock_id];
  
    for(auto &it : request_q.request_queue_) {
        if(it.txn_id_ == txn->get_transaction_id()) {   // 加锁队列已有该事务的锁
            if(it.lock_mode_ == LockMode::EXLUCSIVE || it.lock_mode_ == LockMode::S_IX || it.lock_mode_ == LockMode::SHARED) {
                return true;
            }else if(it.lock_mode_ == LockMode::INTENTION_SHARED){
                // 事务已加IS锁
                if(request_q.group_lock_mode_ == GroupLockMode::IS || request_q.group_lock_mode_ == GroupLockMode::S) {
                    it.lock_mode_ = LockMode::SHARED;
                    request_q.group_lock_mode_ = GroupLockMode::S;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }else {
                // 事务已加IX锁
                int num = 0;
                for(auto const &it2 : request_q.request_queue_) {
                    if(it2.lock_mode_ == LockMode::INTENTION_EXCLUSIVE) {
                        num++;
                    }
                }
                if(num == 1) {  //升级SIX锁，需要加锁队列只有这一个IX锁
                    it.lock_mode_ = LockMode::S_IX;
                    request_q.group_lock_mode_ = GroupLockMode::SIX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 申请锁
    if(request_q.group_lock_mode_ == GroupLockMode::NON_LOCK ||
        request_q.group_lock_mode_ == GroupLockMode::S || 
        request_q.group_lock_mode_ == GroupLockMode::IS) {
        
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);

        request.granted_ = true;

        request_q.group_lock_mode_ = GroupLockMode::S;
        request_q.request_queue_.emplace_back(request);
        return true;
    }else { // 不允许加锁
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }
    return true;
}

/**
 * @description: 申请表级写锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_exclusive_on_table(Transaction* txn, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want X T"<<std::endl;

    std::scoped_lock lock{latch_};

    if(!check_lock(txn)){
        return false;
    }
    // 锁请求对象
    LockDataId lock_id = LockDataId(tab_fd, LockDataType::TABLE);

    if(!lock_table_.count(lock_id)) {     //全局锁
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }
   
    LockRequest request(txn->get_transaction_id(), LockMode::EXLUCSIVE);     //lock request
    LockRequestQueue &request_q = lock_table_[lock_id];
  
    for(auto &it : request_q.request_queue_) {
        if(it.txn_id_ == txn->get_transaction_id()) {
            if(it.lock_mode_ == LockMode::EXLUCSIVE) {
                return true;    // 事务已加X锁
            }else {
                // 事务已加锁但非X
                if(request_q.request_queue_.size() == 1) {  // 只能有此事务加锁
                    it.lock_mode_ = LockMode::EXLUCSIVE;
                    request_q.group_lock_mode_ = GroupLockMode::X;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 申请锁
    if(request_q.group_lock_mode_ == GroupLockMode::NON_LOCK) {
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);
        request.granted_ = true;
        request_q.group_lock_mode_ = GroupLockMode::X;
        request_q.request_queue_.emplace_back(request);
        return true;
    }else {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }
    return true;
}

/**
 * @description: 申请表级意向读锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_IS_on_table(Transaction* txn, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want IS T"<<std::endl;

    std::scoped_lock lock{latch_};

    if(!check_lock(txn)){
        return false;
    }
    //锁请求对象
    LockDataId lock_id = LockDataId(tab_fd, LockDataType::TABLE);
    
    if(!lock_table_.count(lock_id)) {     //查看全局表锁
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }
    //lock request
    LockRequest request(txn->get_transaction_id(), LockMode::INTENTION_SHARED);
    LockRequestQueue &request_q = lock_table_[lock_id];
    // 事务已加锁
    for(auto &it : request_q.request_queue_) {
        if(it.txn_id_ == txn->get_transaction_id()) {
            return true;    // IS 级别最低
        }
    }

    // 需要申请锁
    if(request_q.group_lock_mode_ != GroupLockMode::X) {
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);
        request.granted_ = true;
        if(request_q.group_lock_mode_ == GroupLockMode::NON_LOCK) {
            request_q.group_lock_mode_ = GroupLockMode::IS;
        }
        request_q.request_queue_.emplace_back(request);
        return true;
    }else {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }
    return true;
}

/**
 * @description: 申请表级意向写锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_IX_on_table(Transaction* txn, int tab_fd) {

    std::cout<<txn->get_transaction_id()<<" want IX T"<<std::endl;

    std::scoped_lock lock{latch_};

    if(!check_lock(txn)){
        return false;
    }
    //锁请求对象
    LockDataId lock_id = LockDataId(tab_fd, LockDataType::TABLE);
  
    if(!lock_table_.count(lock_id)) {  //全局表锁
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_id), std::forward_as_tuple());
    }
    // lock request
    LockRequest request(txn->get_transaction_id(), LockMode::INTENTION_EXCLUSIVE);
    LockRequestQueue &request_q = lock_table_[lock_id];

    for(auto &it : request_q.request_queue_) {
        if(it.txn_id_ == txn->get_transaction_id()) {
            if(it.lock_mode_ == LockMode::INTENTION_EXCLUSIVE || it.lock_mode_ == LockMode::S_IX || it.lock_mode_ == LockMode::EXLUCSIVE) {
                return true;
            }else if (it.lock_mode_ == LockMode::SHARED){
                // 事务已加S锁
                int num = 0;
                for(auto const &it2 : request_q.request_queue_) {
                    if(it2.lock_mode_ == LockMode::SHARED) {
                        num++;
                    }
                }
                if(num == 1) {
                    it.lock_mode_ = LockMode::S_IX;
                    request_q.group_lock_mode_ = GroupLockMode::SIX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }else {
                // 事务已加IS锁
                if(request_q.group_lock_mode_ == GroupLockMode::IS || request_q.group_lock_mode_ == GroupLockMode::IX) {
                    it.lock_mode_ = LockMode::INTENTION_EXCLUSIVE;
                    request_q.group_lock_mode_ = GroupLockMode::IX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 申请锁
    if(request_q.group_lock_mode_ == GroupLockMode::NON_LOCK || request_q.group_lock_mode_ == GroupLockMode::IS || request_q.group_lock_mode_ == GroupLockMode::IX) {
        auto lock_set = txn->get_lock_set();
        lock_set->emplace(lock_id);
        request.granted_ = true;
        request_q.group_lock_mode_ = GroupLockMode::IX;
        request_q.request_queue_.emplace_back(request);
        return true;
    }else {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
    }
    return true;
}

/**
 * @description: 释放锁
 * @return {bool} 返回解锁是否成功
 * @param {Transaction*} txn 要释放锁的事务对象指针
 * @param {LockDataId} lock_data_id 要释放的锁ID
 */
bool LockManager::unlock(Transaction* txn, LockDataId lock_data_id) {

    std::cout<<txn->get_transaction_id()<<" want unlock "<<std::endl;

    std::scoped_lock lock{latch_};
    if(!check_unlock(txn)){
        return false;
    }
    
    if(!lock_table_.count(lock_data_id)) {  //查全局表，若没有则返回
        return true;
    }
    // request queue
    LockRequestQueue &request_q = lock_table_[lock_data_id];

    // 在锁请求队列中删除该事务
    for(auto it = request_q.request_queue_.begin(); it != request_q.request_queue_.end(); it++) {
        if(it->txn_id_ == txn->get_transaction_id()) {
            std::cout<<it->lock_mode_<<std::endl;
            request_q.request_queue_.erase(it);
            break;
        }
    }

    int IS_num = 0, IX__num = 0, S_num = 0, SIX_num = 0, X_num = 0;
    for(auto const &it : request_q.request_queue_) {
        if (it.lock_mode_ == LockMode::INTENTION_SHARED) {
            IS_num++;
        } else if (it.lock_mode_ == LockMode::INTENTION_EXCLUSIVE) {
            IX__num++;
        } else if (it.lock_mode_ == LockMode::SHARED) {
            S_num++;
        } else if (it.lock_mode_ == LockMode::EXLUCSIVE) {
            X_num++;
        } else if (it.lock_mode_ == LockMode::S_IX) {
            SIX_num++;
        } else continue;
    }
                // 更改 group_lock_mode_
    if(X_num) {
        request_q.group_lock_mode_ = GroupLockMode::X;
    }else if(SIX_num) {
        request_q.group_lock_mode_ = GroupLockMode::SIX;
    }else if(IX__num) {
        request_q.group_lock_mode_ = GroupLockMode::IX;
    }else if(S_num) {
        request_q.group_lock_mode_ = GroupLockMode::S;
    }else if(IS_num) {
        request_q.group_lock_mode_ = GroupLockMode::IS;
    }else {
        request_q.group_lock_mode_ = GroupLockMode::NON_LOCK;
    }
    return true;
}

bool LockManager::check_lock(Transaction *txn) {

    if (txn->get_state() == TransactionState::COMMITTED ||
        txn->get_state() == TransactionState::ABORTED) {
        return false;
    } else if (txn->get_state() == TransactionState::DEFAULT) {
        txn->set_state(TransactionState::GROWING);
        return true;
    } else if (txn->get_state() == TransactionState::GROWING) {
        return true;
    } else if (txn->get_state() == TransactionState::SHRINKING) {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::LOCK_ON_SHIRINKING);
    } else {
        throw RMDBError("事务状态无效：" + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    return false;
}


bool LockManager::check_unlock(Transaction *txn) {
    
    if (txn->get_state() == TransactionState::COMMITTED ||
        txn->get_state() == TransactionState::ABORTED) {
        return false;
    } else if (txn->get_state() == TransactionState::DEFAULT) {
        return true;
    } else if (txn->get_state() == TransactionState::GROWING) {
        txn->set_state(TransactionState::SHRINKING);
        return true;
    } else if (txn->get_state() == TransactionState::SHRINKING) {
        return true;
    } else {
        throw RMDBError("事务状态无效: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    return false;
}
