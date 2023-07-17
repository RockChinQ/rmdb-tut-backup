#pragma once
#include "execution_defs.h"
#include "common/common.h"
#include "index/ix.h"
#include "system/sm.h"

class ConditionDependedExecutor {
    protected:
        std::string tab_name_;
        SmManager *sm_manager_;
    public:
        ConditionDependedExecutor() = default;
        ConditionDependedExecutor(std::string tab_name, SmManager *sm_manager) : tab_name_(tab_name), sm_manager_(sm_manager) {}
        
    
    Value get_record_value(const RmRecord &record, const TabCol &col) {
        Value val;

        auto col_meta = sm_manager_->db_.get_table(tab_name_).get_col(col.col_name)[0];
        
        val.type = col_meta.type;
        
        if (col_meta.type == TYPE_INT) {
            val.set_int(*(int *)(record.data + col_meta.offset));
        } else if (col_meta.type == TYPE_FLOAT) {
            val.set_float(*(float *)(record.data + col_meta.offset));
        } else if (col_meta.type == TYPE_STRING) {
            
            int offset = col_meta.offset;
            int len = col_meta.len;

            val.set_str(std::string(record.data + offset, len));
        }

        // TODO: BIGINT

        return val;
    }

    bool check_conds(const std::vector<Condition> &conds, const RmRecord &record) {
        for (auto &cond : conds) {
            std::cout<<"check_conds: "<<cond.lhs_col.col_name<<std::endl;
            if (!check_cond(cond, record)) {
                return false;
            }
        }
        return true;
    }

    bool check_cond(const Condition &cond, const RmRecord &record) {
        Value left = get_record_value(record, cond.lhs_col);

        Value right;

        if (cond.is_rhs_val) {
            right = cond.rhs_val;
        } else {
            right = get_record_value(record, cond.rhs_col);
        }

        // 把双方的int都转成float

        if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
            left.set_float(left.int_val);
        } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
            right.set_float(right.int_val);
        }

        float cp_res = 0;

        if (left.type == TYPE_INT && right.type == TYPE_INT) {

            cp_res = left.int_val - right.int_val;
        } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {

            cp_res = left.float_val - right.float_val;
        } else if (left.type == TYPE_STRING && right.type == TYPE_STRING) {
            cp_res = left.str_val.compare(right.str_val);

            std::cout<<"check_cond: "<<left.str_val<<" "<<right.str_val<<std::endl;
        } else {
            throw InternalError("Unexpected field type");
        }

        std::cout<<"check_cond: "<<cp_res<<std::endl;

        switch (cond.op) {
            case OP_EQ:
                return cp_res == 0;
            case OP_NE:
                return cp_res != 0;
            case OP_LT:
                return cp_res < 0;
            case OP_LE:
                return cp_res <= 0;
            case OP_GT:
                return cp_res > 0;
            case OP_GE:
                return cp_res >= 0;
            default:
                throw InternalError("Unexpected field type");
        }
    }

};