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

class ProjectionExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> prev_;        // 投影节点的儿子节点
    std::vector<ColMeta> cols_;                     // 需要投影的字段
    size_t len_;                                    // 字段总长度
    std::vector<size_t> sel_idxs_;                  

   public:
    ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev, const std::vector<TabCol> &sel_cols) {
        prev_ = std::move(prev);

        std::cout<<"ProjectionExecutor"<<std::endl;

        size_t curr_offset = 0;

        std::cout<<"is prev_ nullptr?"<<(prev_==nullptr)<<std::endl;
        std::cout<<"what is prev_?"<<prev_->getType()<<std::endl;

        auto &prev_cols = prev_->cols();

        std::cout<<"ProjectionExecutor prev_cols size "<<prev_cols.size()<<std::endl;
        for (auto &sel_col : sel_cols) {
            auto pos = get_col(prev_cols, sel_col);
            sel_idxs_.push_back(pos - prev_cols.begin());
            auto col = *pos;
            col.offset = curr_offset;
            curr_offset += col.len;
            cols_.push_back(col);
        }
        len_ = curr_offset;
    }

    // ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev, const std::vector<TabCol> &sel_cols) {
    //     if (prev == nullptr) {
    //         std::cout << "prev is nullptr!" << std::endl;
    //     }

    //     auto &prev_cols = prev_->cols();
    //     prev_ = std::move(prev);

    //     size_t curr_offset = 0;

    //     if (prev_cols.empty()) {
    //         std::cout << "prev_cols is empty!" << std::endl;
    //     }

    //     for (auto &sel_col : sel_cols) {
    //         auto pos = get_col(prev_cols, sel_col);

    //         if (pos == prev_cols.end()) {
    //             std::cout << "pos is end!" << std::endl;
    //         }

    //         sel_idxs_.push_back(pos - prev_cols.begin());
    //         auto col = *pos;
    //         col.offset = curr_offset;
    //         curr_offset += col.len;
    //         cols_.push_back(col);
    //     }

    //     len_ = curr_offset;

    //     std::cout << "ProjectionExecutor end" << std::endl;
    // }

    std::string getType() override { return "ProjectionExecutor"; }


    void beginTuple() override {
        prev_->beginTuple();
    }

    void nextTuple() override {
        prev_->nextTuple();
    }

    bool is_end() const override {
        return prev_->is_end();
    }

    std::unique_ptr<RmRecord> Next() override {
        auto record = prev_->Next();
        if (record == nullptr) {
            return nullptr;
        }
        auto new_record = std::make_unique<RmRecord>(len_);
        for (size_t i = 0; i < sel_idxs_.size(); i++) {
            auto &col = cols_[i];
            auto &prev_col = prev_->cols()[sel_idxs_[i]];
            memcpy(new_record->data + col.offset, record->data + prev_col.offset, col.len);
        }
        return new_record;
    }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    Rid &rid() override { return _abstract_rid; }

    size_t tupleLen() const override { return len_; }
};