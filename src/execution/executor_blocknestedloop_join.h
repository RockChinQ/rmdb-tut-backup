#pragma once

#include <memory>
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "exexution_conddep.h"
#include "index/ix.h"
#include "system/sm.h"
#include "record/rm_defs.h"

class JoinBuffer {
public:
    const static int JOIN_BUFFER_SIZE = 1000;
    std::unique_ptr<RmRecord> buffer_[JOIN_BUFFER_SIZE];
    size_t size_; // 记录大小
    size_t pos_;

    JoinBuffer() : size_(0), pos_(0) {}

    void push_back(std::unique_ptr<RmRecord> record) {
        assert(!is_full());    
        buffer_[size_] = std::move(record);
        size_++;
    }

    void beginTuple() {
        pos_ = 0;
    }

    void nextTuple() {
        pos_++;
    }

    std::unique_ptr<RmRecord>* get_record() {
        assert(!is_end());
        return &buffer_[pos_];
    }

    void reset() {
        memset(buffer_, 0, sizeof(buffer_));
        pos_ = 0;
        size_ = 0;
    }
 
    bool is_full() {
        return size_ >= JOIN_BUFFER_SIZE;
    }

    bool is_end() {
        return pos_ >= size_;
    }

};


class ExecutorJoiningBuffer {
public:
    std::unique_ptr<AbstractExecutor>* prev_;
    std::unique_ptr<JoinBuffer> buffer_;
    ExecutorJoiningBuffer(std::unique_ptr<AbstractExecutor>* prev) : prev_(prev) {
        buffer_ = std::make_unique<JoinBuffer>();
    }

    void beginBuffer() {
        (*prev_)->beginTuple(); 
        buffer_->reset();
        while(!(*prev_)->is_end() && !buffer_->is_full()) {
            buffer_->push_back(std::move((*prev_)->Next()));
            (*prev_)->nextTuple();
        }
    }

    void nextBuffer() {
        assert(!is_end());
        buffer_->reset();
        while(!(*prev_)->is_end() && !buffer_->is_full()) {
            buffer_->push_back(std::move((*prev_)->Next()));
            (*prev_)->nextTuple();
        }
    }

    std::unique_ptr<JoinBuffer>* Next() {
        // assert(!is_end());
        return &buffer_;
    }

    bool is_end() {
        return buffer_->size_ == 0;
    }
};

class BlockNestedLoopJoinExecutor : public AbstractExecutor, public ConditionDependedExecutor {
   private:
    std::unique_ptr<AbstractExecutor> left_;    // 左儿子节点（需要join的表）
    std::unique_ptr<AbstractExecutor> right_;   // 右儿子节点（需要join的表）
    size_t len_;                                // join后获得的每条记录的长度
    std::vector<ColMeta> cols_;                 // join后获得的记录的字段

    std::vector<Condition> conds_;          // join条件
    bool isend;

    // join buffer
    std::unique_ptr<ExecutorJoiningBuffer> left_blocks_;
    std::unique_ptr<ExecutorJoiningBuffer> right_blocks_;
    std::unique_ptr<JoinBuffer>* left_join_buffer_;
    std::unique_ptr<JoinBuffer>* right_join_buffer_;

   public:
    BlockNestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right, 
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
        conds_ = std::move(conds);

        // 初始化join buffer
        left_blocks_ = std::make_unique<ExecutorJoiningBuffer>(&left_);
        right_blocks_ = std::make_unique<ExecutorJoiningBuffer>(&right_);
    }


    const std::vector<ColMeta> &cols() const {
        return cols_;
    };

    bool is_end() const override { 
        return isend; 
    };

    size_t tupleLen() const { return len_; };

    std::string getType() { return "BlockNestedLoopJoinExecutor"; };

    // 
    void beginTuple() override {
        // 1. 初始化 left blocks, right blocks, left join buffer, right join buffer
        left_blocks_->beginBuffer();
        right_blocks_->beginBuffer();
        left_join_buffer_ = std::move(left_blocks_->Next());
        right_join_buffer_ = std::move(right_blocks_->Next());
        (*left_join_buffer_)->beginTuple();
        (*right_join_buffer_)->beginTuple();
        // 2. 初始化 isend并开启循环寻找第一个符合要求的节点
        isend = false;
        find_next_valid_tuple();
    }

    void nextTuple() override {
        assert(!is_end());

        (*right_join_buffer_)->nextTuple();
        // 2. 找到下一个合法的tuple
        find_next_valid_tuple();
    }

    std::unique_ptr<RmRecord> Next() override {
        assert(!is_end());
        // 1. 取left_record和right_record
        auto left_record = (*left_join_buffer_)->get_record();
        auto right_record = (*right_join_buffer_)->get_record();
        // 2. 合并到一起
        auto ret = std::make_unique<RmRecord>(len_);
        memcpy(ret->data, (*left_record)->data, (*left_record)->size);
        memcpy(ret->data + (*left_record)->size, (*right_record)->data, (*right_record)->size);
        return ret;
    }

    Rid &rid() override { return _abstract_rid; }

private:

    // 找到下一个符合fed_cond的tuple
    void find_next_valid_tuple() {
        // 1.开启循环体，四重循环
        while(!left_blocks_->is_end()) {
            while(!right_blocks_->is_end()) {
                while(!(*left_join_buffer_)->is_end()) {
                    auto left_record = (*left_join_buffer_)->get_record();
                    while(!(*right_join_buffer_)->is_end()) {
                        // 寻找符合条件的tuple
                        auto right_record = (*right_join_buffer_)->get_record();
                        // 检查是否符合fed_cond
                        bool is_fit = true;
                        for(auto cond : conds_) {
                            // 取left value
                            
                            auto left_cols = left_->cols();
                            auto left_col = *(left_->get_col(left_cols, cond.lhs_col));
                            auto left_value = get_record_value(*left_record, left_col);

                            // 取right value
                            Value right_value;
                            if(cond.is_rhs_val) {
                                right_value = cond.rhs_val;
                            }else {
                                auto right_cols = right_->cols();
                                auto right_col = *(right_->get_col(right_cols, cond.rhs_col));
                                right_value = get_record_value(*right_record, right_col);
                            }

                            // 比较是否符合条件

                            if(!check_cond(left_value, right_value, cond)) {
                                is_fit = false;
                                break;
                            }
                        }
                        // 如果符合要求，则返回
                        if(is_fit) {
                            return ;
                        }
                        (*right_join_buffer_)->nextTuple();
                    }
                    // right_join_buffer_遍历完毕
                    // left_join_buffer_+1, right_join buffer重新开始遍历
                    (*left_join_buffer_)->nextTuple();
                    (*right_join_buffer_)->beginTuple();
                }
                // left join buffer和right join buffer都遍历完毕
                // left join buffer重新开始遍历，right join buffer刷新
                (*left_join_buffer_)->beginTuple();
                right_blocks_->nextBuffer();
                right_join_buffer_ = right_blocks_->Next();
                (*right_join_buffer_)->beginTuple();
            }
            // right blocks中的所有buffer都遍历过一遍了
            // left blocks + 1， right blocks重新遍历
            left_blocks_->nextBuffer();
            left_join_buffer_ = left_blocks_->Next();
            (*left_join_buffer_)->beginTuple();
            right_blocks_->beginBuffer();
            right_join_buffer_ = right_blocks_->Next();
            (*right_join_buffer_)->beginTuple();
        }
        // 遍历结束，没有符合要求的tuple了
        isend = true;
        return ;
    }
};