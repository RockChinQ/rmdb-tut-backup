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

class SortExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> prev_;
    ColMeta cols_;                              // 框架中只支持一个键排序，需要自行修改数据结构支持多个键排序
    size_t tuple_num_;
    bool is_desc_;
    std::vector<size_t> used_tuple;
    std::unique_ptr<RmRecord> current_tuple;
    std::vector<std::unique_ptr<RmRecord>> tuples_;

     // order_cols，保存多个排序键
    std::vector<OrderByCol> order_cols_;
    // 增加limit_，限制输出元组个数
    int limit_;
    int count_;

   public:
    SortExecutor(std::unique_ptr<AbstractExecutor> prev, std::vector<OrderByCol> order_cols, int limit)
    {
        prev_ = std::move(prev);
        order_cols_ = order_cols;
        limit_ = limit;
        count_ = 0;
        tuple_num_ = 0;
        used_tuple.clear();
    }

    std::string getType() override { return "SortExecutor"; }

    // 自定义比较类
    class RmCompare : AbstractExecutor, public ConditionDependedExecutor {
    public:
        std::vector<OrderByCol> order_cols_;
        std::unique_ptr<AbstractExecutor> &prev_;
        RmCompare(std::vector<OrderByCol> order_cols, std::unique_ptr<AbstractExecutor> &prev) :
            order_cols_(order_cols), prev_(prev) { }
        bool operator()(const std::unique_ptr<RmRecord> &lhs, const std::unique_ptr<RmRecord> &rhs) {
            for (auto &order_col : order_cols_)
            {
                auto cols = prev_->cols();
                auto col_meta = *get_col(cols, order_col.tabcol);
                Value left_value = get_record_value(lhs, col_meta);
                Value right_value = get_record_value(rhs, col_meta);
                Condition cond;
                cond.op = OP_GT;
                bool flag = check_cond(left_value, right_value, cond);
                cond.op = OP_EQ;
                bool is_equal = check_cond(left_value, right_value, cond);
                if(is_equal) {
                    continue;
                }else if((!flag && order_col.is_desc) || (flag && !order_col.is_desc))
                {
                    return false;
                }else{
                    return true;
                }
            }
            return true;
        }

        Rid &rid() override { return _abstract_rid; }

        std::unique_ptr<RmRecord> Next() override { return std::make_unique<RmRecord>(); }
    };

    void beginTuple() override { 
        used_tuple.clear();
        for( prev_->beginTuple(); !prev_->is_end(); prev_->nextTuple()){
            auto tuple = prev_ -> Next();
            tuples_.push_back(std::move(tuple));
        }
        std::sort(tuples_.begin(), tuples_.end(), RmCompare(order_cols_, prev_));
        count_ = 0;
    }

    void nextTuple() override {
        count_++;
    }

    std::unique_ptr<RmRecord> Next() override {
        return std::move(tuples_[count_]);
    }

    // 实现cols方法，上层需要调用
    const std::vector<ColMeta> &cols() const
    {
        return prev_->cols();
    };

    bool is_end() const override { 
        if(limit_ != -1 && count_ >= limit_) {
            return true;
        }
        return count_ >= (int)tuples_.size(); 
    };

    Rid &rid() override { return _abstract_rid; }
};