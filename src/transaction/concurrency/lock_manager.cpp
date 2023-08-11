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


// 加锁检查
bool LockManager::lock_check(Transaction *txn) {
    switch (txn->get_state())
    {
    // 1. 如果已经commit或者abort，则不能再获取锁
    case TransactionState::COMMITTED:
    case TransactionState::ABORTED: {
        return false;
    }
    // 2. 如果是default状态，说明之前没有获取过锁，那么第一个取得锁，需要改变txn的状态为growing
    case TransactionState::DEFAULT: {
        txn->set_state(TransactionState::GROWING);
    }
    // 3. 如果是growing状态，则直接返回true
    case TransactionState::GROWING: {
        return true;
    }
    // 4. 如果是shrinking状态，违反两阶段规则，强制abort
    case TransactionState::SHRINKING: {
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::LOCK_ON_SHIRINKING);
    }
    default:
        throw RMDBError("InValid transaction state in " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    return false;
}

// 释放锁检查
bool LockManager::unlock_check(Transaction * txn) {
    switch (txn->get_state())
    {
    // 1. 如果已经commit或者abort，则不能再释放锁
    case TransactionState::COMMITTED:
    case TransactionState::ABORTED: {
        return false;
    }
    // 2. 如果是default状态，说明之前没有获取过锁，也没有锁可以释放，释放没有获得的锁算true还是false???这里暂定为true
    // TODO:
    case TransactionState::DEFAULT: {
        return true;
    }
    // 3. 如果是growing状态，则进入shrink阶段
    case TransactionState::GROWING: {
        txn->set_state(TransactionState::SHRINKING);
    }
    // 4. 如果是shrinking状态，则直接返回true
    case TransactionState::SHRINKING: {
        return true;
    }
    default:
        throw RMDBError("InValid transaction state in " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    return false;
}

/**
 * @description: 申请行级共享锁
 * @return {bool} 加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {Rid&} rid 加锁的目标记录ID 记录所在的表的fd
 * @param {int} tab_fd
 */
bool LockManager::lock_shared_on_record(Transaction* txn, const Rid& rid, int tab_fd) {
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, rid, LockDataType::RECORD);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::SHARED);
    auto &request_queue = lock_table_[lock_data_id];

    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            return true;
        }
    }

    // 7. 申请锁，申请失败就abort
    if(request_queue.group_lock_mode_ == GroupLockMode::S || request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK) {
        txn->get_lock_set()->emplace(lock_data_id);
        request.granted_ = true;
        request_queue.group_lock_mode_ = GroupLockMode::S;
        request_queue.request_queue_.emplace_back(request);
    } else {
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, rid, LockDataType::RECORD);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::EXLUCSIVE);
    auto &request_queue = lock_table_[lock_data_id];

    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            if(req.lock_mode_ == LockMode::EXLUCSIVE) {
                // 6.1 该事务已经持有X锁
                return true;
            }else {
                // 6.2 该事务持有了S锁，需要升级为X锁，只有当请求列表中没有其他事务持有锁才能成功
                if(request_queue.group_lock_mode_ == GroupLockMode::S && request_queue.request_queue_.size() == 1) {
                    req.lock_mode_ = LockMode::EXLUCSIVE;
                    request_queue.group_lock_mode_ = GroupLockMode::X;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 7. 该事务没有持有该对象的锁，要申请X锁，条件是当前对象没有被持有任何锁
    if(request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK) {
        txn->get_lock_set()->emplace(lock_data_id);
        request.granted_ = true;
        request_queue.group_lock_mode_ = GroupLockMode::X;
        request_queue.request_queue_.emplace_back(request);
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, LockDataType::TABLE);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::SHARED);
    auto &request_queue = lock_table_[lock_data_id];
    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            if(req.lock_mode_ == LockMode::EXLUCSIVE || req.lock_mode_ == LockMode::S_IX || req.lock_mode_ == LockMode::SHARED) {
                // 6.1 该事务已经持有S锁或者更高级的锁，例如X,S_IX,S
                return true;
            }else if(req.lock_mode_ == LockMode::INTENTION_SHARED){
                // 6.2 该事务持有了IS锁，需要升级为S锁
                if(request_queue.group_lock_mode_ == GroupLockMode::IS || request_queue.group_lock_mode_ == GroupLockMode::S) {
                    req.lock_mode_ = LockMode::SHARED;
                    request_queue.group_lock_mode_ = GroupLockMode::S;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }else {
                // 6.3 该事务持有了IX锁，需要升级为S_IX锁，升级条件为当前仅有一个IX锁
                int num_ix = 0;
                for(auto const &req2 : request_queue.request_queue_) {
                    if(req2.lock_mode_ == LockMode::INTENTION_EXCLUSIVE) {
                        num_ix++;
                    }
                }
                if(num_ix == 1) {
                    req.lock_mode_ = LockMode::S_IX;
                    request_queue.group_lock_mode_ = GroupLockMode::SIX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 7. 事务没有持有该锁，需要申请S锁，申请条件group lock为S,IS,NON_LOCK
    if(request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK ||
        request_queue.group_lock_mode_ == GroupLockMode::S || 
        request_queue.group_lock_mode_ == GroupLockMode::IS) {

        txn->get_lock_set()->emplace(lock_data_id);

        request.granted_ = true;

        request_queue.group_lock_mode_ = GroupLockMode::S;
        request_queue.request_queue_.emplace_back(request);
        return true;
    }else {
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, LockDataType::TABLE);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::EXLUCSIVE);
    auto &request_queue = lock_table_[lock_data_id];
    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            if(req.lock_mode_ == LockMode::EXLUCSIVE) {
                // 6.1 该事务已经持有X锁
                return true;
            }else {
                // 6.2 该事务持有了某种锁，需要升级为X锁，升级条件为当前仅有该事务持有锁
                if(request_queue.request_queue_.size() == 1) {
                    req.lock_mode_ = LockMode::EXLUCSIVE;
                    request_queue.group_lock_mode_ = GroupLockMode::X;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 7. 事务没有持有X锁，需要申请，申请条件NON_LOCK
    if(request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK) {
        txn->get_lock_set()->emplace(lock_data_id);
        request.granted_ = true;
        request_queue.group_lock_mode_ = GroupLockMode::X;
        request_queue.request_queue_.emplace_back(request);
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, LockDataType::TABLE);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::INTENTION_SHARED);
    auto &request_queue = lock_table_[lock_data_id];
    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            // 没有比IS锁更低级的锁
            return true;
        }
    }

    // 7. 事务没有持有IS锁，需要申请，申请条件为grouplock不为X
    if(request_queue.group_lock_mode_ != GroupLockMode::X) {
        txn->get_lock_set()->emplace(lock_data_id);
        request.granted_ = true;
        if(request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK) {
            request_queue.group_lock_mode_ = GroupLockMode::IS;
        }
        request_queue.request_queue_.emplace_back(request);
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查，如果事务已经进入shrinking阶段，则不能获取锁
    if(!lock_check(txn)){
        return false;
    }
    // 3. 创建锁请求对象
    auto lock_data_id = LockDataId(tab_fd, LockDataType::TABLE);
    // 4. 如果锁表中还不存在该对象，则构造该对象
    if(!lock_table_.count(lock_data_id)) {
        lock_table_.emplace(std::piecewise_construct, std::forward_as_tuple(lock_data_id), std::forward_as_tuple());
    }
    // 5. 构造lock request
    LockRequest request(txn->get_transaction_id(), LockMode::INTENTION_EXCLUSIVE);
    auto &request_queue = lock_table_[lock_data_id];
    // 6. 查看是否该事务已经持有对应的锁
    for(auto &req : request_queue.request_queue_) {
        if(req.txn_id_ == txn->get_transaction_id()) {
            if(req.lock_mode_ == LockMode::INTENTION_EXCLUSIVE || req.lock_mode_ == LockMode::S_IX || req.lock_mode_ == LockMode::EXLUCSIVE) {
                // 6.1 该事务已经持有IX锁或者更高级的锁
                return true;
            }else if (req.lock_mode_ == LockMode::SHARED){
                // 6.2 该事务持有S锁，需要升级为S_IX锁，升级条件为该数据对象仅有一个S锁
                int num_s = 0;
                for(auto const &req2 : request_queue.request_queue_) {
                    if(req2.lock_mode_ == LockMode::SHARED) {
                        num_s++;
                    }
                }
                if(num_s == 1) {
                    req.lock_mode_ = LockMode::S_IX;
                    request_queue.group_lock_mode_ = GroupLockMode::SIX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }else {
                // 6.3 该事务持有IS锁，需要升级为IX锁，升级条件为IS，IX
                if(request_queue.group_lock_mode_ == GroupLockMode::IS || request_queue.group_lock_mode_ == GroupLockMode::IX) {
                    req.lock_mode_ = LockMode::INTENTION_EXCLUSIVE;
                    request_queue.group_lock_mode_ = GroupLockMode::IX;
                    return true;
                }else {
                    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
    }

    // 7. 事务没有持有IX锁，需要申请，申请条件NON_LOCK，IS，IX
    if(request_queue.group_lock_mode_ == GroupLockMode::NON_LOCK || request_queue.group_lock_mode_ == GroupLockMode::IS || request_queue.group_lock_mode_ == GroupLockMode::IX) {
        txn->get_lock_set()->emplace(lock_data_id);
        request.granted_ = true;
        request_queue.group_lock_mode_ = GroupLockMode::IX;
        request_queue.request_queue_.emplace_back(request);
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
    // 1. 保护全局锁表
    std::scoped_lock lock{latch_};
    // 2. 两阶段检查
    if(!unlock_check(txn)){
        return false;
    }
    // 3. 如果锁表中还不存在该对象，则直接返回true
    if(!lock_table_.count(lock_data_id)) {
        return true;
    }
    // 4. 获得request queue
    auto &request_queue = lock_table_[lock_data_id];
    // 5. 遍历queue并删除该事务的锁请求
    for(auto req = request_queue.request_queue_.begin(); req != request_queue.request_queue_.end(); req++) {
        if(req->txn_id_ == txn->get_transaction_id()) {
            request_queue.request_queue_.erase(req);
            break;
        }
    }
    // 6. 更新request queue的元信息
    int IS_lock_num = 0, IX_lock_num = 0, S_lock_num = 0, SIX_lock_num = 0, X_lock_num = 0;
    for(auto const &req : request_queue.request_queue_) {
        switch (req.lock_mode_)
        {
        case LockMode::INTENTION_SHARED: {
            IS_lock_num++;
            break;
        }
        case LockMode::INTENTION_EXCLUSIVE: {
            IX_lock_num++;
            break;
        }
        case LockMode::SHARED: {
            S_lock_num++;
            break;
        }
        case LockMode::EXLUCSIVE: {
            X_lock_num++;
            break;
        }
        case LockMode::S_IX: {
            SIX_lock_num++;
            break;
        }
        default:
            break;
        }
    }
    if(X_lock_num > 0) {
        request_queue.group_lock_mode_ = GroupLockMode::X;
    }else if(SIX_lock_num > 0) {
        request_queue.group_lock_mode_ = GroupLockMode::SIX;
    }else if(IX_lock_num > 0) {
        request_queue.group_lock_mode_ = GroupLockMode::IX;
    }else if(S_lock_num > 0) {
        request_queue.group_lock_mode_ = GroupLockMode::S;
    }else if(IS_lock_num > 0) {
        request_queue.group_lock_mode_ = GroupLockMode::IS;
    }else {
        request_queue.group_lock_mode_ = GroupLockMode::NON_LOCK;
    }
    return true;
}