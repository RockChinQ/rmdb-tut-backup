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
#include "common/common.h"
#include "index/ix.h"
#include "system/sm.h"

class AbstractExecutor {
   public:
    std::string tab_name_;
    SmManager *sm_manager_;
    Rid _abstract_rid;

    Context *context_;

    virtual ~AbstractExecutor() = default;

    virtual size_t tupleLen() const { return 0; };

    virtual const std::vector<ColMeta> &cols() const {
        std::vector<ColMeta> *_cols = nullptr;
        return *_cols;
    };

    virtual std::string getType() { return "AbstractExecutor"; };

    virtual void beginTuple(){};

    virtual void nextTuple(){};

    virtual bool is_end() const { return true; };

    virtual Rid &rid() = 0;

    virtual std::unique_ptr<RmRecord> Next() = 0;

    virtual ColMeta get_col_offset(const TabCol &target) { return ColMeta();};

    std::vector<ColMeta>::const_iterator get_col(const std::vector<ColMeta> &rec_cols, const TabCol &target) {
        auto pos = std::find_if(rec_cols.begin(), rec_cols.end(), [&](const ColMeta &col) {
            return col.tab_name == target.tab_name && col.name == target.col_name;
        });
        if (pos == rec_cols.end()) {
            throw ColumnNotFoundError(target.tab_name + '.' + target.col_name);
        }
        return pos;
    }
    
    Value get_record_value(const RmRecord &record, const TabCol &col) {
        Value val;

        auto col_meta = sm_manager_->db_.get_table(tab_name_).get_col(col.col_name)[0];
        
        val.type = col_meta.type;
        
        if (col_meta.type == TYPE_INT) {
            val.set_int(*(int *)(record.data + col_meta.offset));
        } else if (col_meta.type == TYPE_FLOAT) {
            val.set_float(*(float *)(record.data + col_meta.offset));
        } else if (col_meta.type == TYPE_STRING) {
            val.set_str(std::string(record.data + col_meta.offset));
        }

        // TODO: BIGINT

        return val;
    }

    bool check_cond(const Condition &cond, const RmRecord &record) {
        Value left = get_record_value(record, cond.lhs_col);

        Value right;

        if (cond.is_rhs_val) {
            right = cond.rhs_val;
        } else {
            right = get_record_value(record, cond.rhs_col);
        }

        switch (cond.op) {
            case OP_EQ:
                return eq(left, right);
                break;
            case OP_NE:
                return ne(left, right);
                break;
            case OP_LT:
                return lt(left, right);
                break;
            case OP_GT:
                return gt(left, right);
                break;
            case OP_LE:
                return le(left, right);
                break;
            case OP_GE:
                return ge(left, right);
                break;
            default:
                return false;
                break;
        }
    }

    bool eq(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return false;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val == right.int_val;
            case TYPE_FLOAT:
                return left.float_val == right.float_val;
            case TYPE_STRING:
                return left.str_val == right.str_val;
            default:
                return false;
        }
    }

    bool ne(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return true;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val != right.int_val;
            case TYPE_FLOAT:
                return left.float_val != right.float_val;
            case TYPE_STRING:
                return left.str_val != right.str_val;
            default:
                return true;
        }
    }

    bool lt(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return false;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val < right.int_val;
            case TYPE_FLOAT:
                return left.float_val < right.float_val;
            case TYPE_STRING:
                return left.str_val < right.str_val;
            default:
                return false;
        }
    }

    bool gt(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return false;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val > right.int_val;
            case TYPE_FLOAT:
                return left.float_val > right.float_val;
            case TYPE_STRING:
                return left.str_val > right.str_val;
            default:
                return false;
        }
    }

    bool le(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return false;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val <= right.int_val;
            case TYPE_FLOAT:
                return left.float_val <= right.float_val;
            case TYPE_STRING:
                return left.str_val <= right.str_val;
            default:
                return false;
        }
    }

    bool ge(const Value &left, const Value &right) {
        if (left.type != right.type) {
            return false;
        }

        switch (left.type) {
            case TYPE_INT:
                return left.int_val >= right.int_val;
            case TYPE_FLOAT:
                return left.float_val >= right.float_val;
            case TYPE_STRING:
                return left.str_val >= right.str_val;
            default:
                return false;
        }
    }
    
};