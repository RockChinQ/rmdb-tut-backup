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

    Value get_record_value(const RmRecord &record, int offset, int len, ColType type){
        Value val;
        val.type = type;

        if (type == TYPE_INT) {
            val.set_int(*(int *)(record.data + offset));
        } else if (type == TYPE_FLOAT) {
            val.set_float(*(float *)(record.data + offset));
        } else if (type == TYPE_STRING) {
            val.set_str(std::string(record.data + offset, len));
        } else if (type == TYPE_DATETIME) {
            uint64_t tmp;
            memcpy((char*)&tmp, record.data + offset, len);
            val.set_datetime(tmp);
        } else if (type == TYPE_BIGINT) {
            int64_t tmp;
            memcpy((char*)&tmp, record.data + offset, len);
            val.set_bigint(tmp); 
        } else {
             throw InvalidTypeError();
        }

        return val;
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
            
            int offset = col_meta.offset;
            int len = col_meta.len;

            val.set_str(std::string(record.data + offset, len));
        } else if (col_meta.type == TYPE_DATETIME) {
            uint64_t tmp;
            memcpy((char*)&tmp, record.data + col_meta.offset, col_meta.len);
            val.set_datetime(tmp);
        } else if (col_meta.type == TYPE_BIGINT) {
            int64_t tmp;
            memcpy((char*)&tmp, record.data + col_meta.offset, col_meta.len);
            val.set_bigint(tmp);
        }
        else {
            throw InvalidTypeError();
        }

        // TODO: BIGINT

        return val;
    }

    // 从Record中取出某一列的Value
    Value get_record_value(const std::unique_ptr<RmRecord> &record, const ColMeta& col_meta) const {
        Value val;
        val.type = col_meta.type;
  
        if(col_meta.type == TYPE_INT) {
            val.set_int(*(int *)(record->data + col_meta.offset));
        }else if(col_meta.type == TYPE_FLOAT) {
            val.set_float(*(float *)(record->data + col_meta.offset));
        }else if(col_meta.type == TYPE_STRING) {
            int offset = col_meta.offset;
            int len = col_meta.len;

            val.set_str(std::string(record->data + offset, len));
        }else if(col_meta.type == TYPE_BIGINT) {
            int64_t tmp;
            memcpy((char*)&tmp, record->data + col_meta.offset, col_meta.len);
            val.set_bigint(tmp);
        }else if(col_meta.type == TYPE_DATETIME) {
            uint64_t tmp;
            memcpy((char*)&tmp, record->data + col_meta.offset, col_meta.len);
            val.set_datetime(tmp);
        }else {
            throw InvalidTypeError();
        }
        val.init_raw(col_meta.len);
        return val;
    }

    bool check_conds(const std::vector<Condition> &conds, const RmRecord &record) {
        for (auto &cond : conds) {
            if (!check_cond(cond, record)) {
                return false;
            }
        }
        return true;
    }

    bool check_cond(Value left, Value right, CompOp op){

        double cp_res = 0;
        if (left.type == TYPE_INT && right.type == TYPE_INT) {
            std::cout<<"left.int_val: "<<left.int_val<<" right.int_val: "<<right.int_val<<std::endl;
            if (left.int_val > right.int_val){
                cp_res = 1;
            } else if (left.int_val < right.int_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
            std::cout<<"left.float_val: "<<left.float_val<<" right.float_val: "<<right.float_val<<std::endl;
            
            if (left.float_val > right.float_val){
                cp_res = 1;
            } else if (left.float_val < right.float_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_STRING && right.type == TYPE_STRING) {

            std::cout<<"left.str_val: "<<left.str_val<<" right.str_val: "<<right.str_val<<std::endl;

            cp_res = left.str_val.compare(right.str_val);

        } else if (left.type==TYPE_DATETIME && right.type == TYPE_DATETIME) {
            std::cout<<"left.datetime_val: "<<left.datetime_val.encode_to_string()<<" right.datetime_val: "<<right.datetime_val.encode_to_string();

            cp_res = left.datetime_val.encode()-right.datetime_val.encode();
        } else if (left.type == TYPE_BIGINT && right.type == TYPE_BIGINT) {
            std::cout<<"left.bigint_val: "<<left.bigint_val<<" right.bigint_val: "<<right.bigint_val<<std::endl;
            
            if (left.bigint_val > right.bigint_val){
                cp_res = 1;
            } else if (left.bigint_val < right.bigint_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } 
        // float&int float&bigint int&float int&bigint bigint&float bigint&int
        else if (left.type == TYPE_INT && right.type == TYPE_FLOAT) {
            std::cout<<"left.int_val: "<<left.int_val<<" right.float_val: "<<right.float_val<<std::endl;
            
            if (left.int_val > right.float_val){
                cp_res = 1;
            } else if (left.int_val < right.float_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_FLOAT && right.type == TYPE_INT) {
            std::cout<<"left.float_val: "<<left.float_val<<" right.int_val: "<<right.int_val<<std::endl;
            if (left.float_val > right.int_val){
                cp_res = 1;
            } else if (left.float_val < right.int_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_INT && right.type == TYPE_BIGINT) {
            std::cout<<"left.int_val: "<<left.int_val<<" right.bigint_val: "<<right.bigint_val<<std::endl;
            
            if (left.int_val > right.bigint_val){
                cp_res = 1;
            } else if (left.int_val < right.bigint_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_BIGINT && right.type == TYPE_INT) {
            std::cout<<"left.bigint_val: "<<left.bigint_val<<" right.int_val: "<<right.int_val<<std::endl;
            
            if (left.bigint_val > right.int_val){
                cp_res = 1;
            } else if (left.bigint_val < right.int_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_BIGINT && right.type == TYPE_FLOAT) {
            std::cout<<"left.bigint_val: "<<left.bigint_val<<" right.float_val: "<<right.float_val<<std::endl;
            
            if (left.bigint_val > right.float_val){
                cp_res = 1;
            } else if (left.bigint_val < right.float_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        } else if (left.type == TYPE_FLOAT && right.type == TYPE_BIGINT) {
            std::cout<<"left.float_val: "<<left.float_val<<" right.bigint_val: "<<right.bigint_val<<std::endl;
            
            if (left.float_val > right.bigint_val){
                cp_res = 1;
            } else if (left.float_val < right.bigint_val){
                cp_res = -1;
            } else {
                cp_res = 0;
            }
        }
        else {
            throw InternalError("Unexpected value pair field type");
        }

        std::cout<<"compare result: "<<cp_res<<std::endl;

        switch (op) {
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
                throw InternalError("Unexpected cond.op field type");
        }
    }

    bool check_cond(Value left, Value right, Condition cond){
        return check_cond(left, right, cond.op);
    }

    bool check_cond(const Condition &cond, const RmRecord &record) {
        Value left = get_record_value(record, cond.lhs_col);

        Value right;

        if (cond.is_rhs_val) {
            right = cond.rhs_val;
        } else {
            right = get_record_value(record, cond.rhs_col);
        }
        return check_cond(left, right, cond);
    }

    SmManager *get_sm_manager() {
        return sm_manager_;
    }

    // bool check_conds(const std::vector<Condition> &conds, const RmRecord &left, const RmRecord &right) {
    //     for (auto &cond : conds) {
    //         if (!check_cond(cond, left, right)) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }


    Value* insert_compatible(ColType targetType, Value sourceValue){
        // 把source转换成目标类型的Value
        Value* targetValue = new Value();

        if (targetType==TYPE_INT){
            if (sourceValue.type==TYPE_INT){
                targetValue->set_int(sourceValue.int_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_FLOAT){
                targetValue->set_int(sourceValue.float_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_BIGINT){
                throw TypeOverflowError("INT", std::to_string(sourceValue.bigint_val));
                return nullptr;
            } else {
                return nullptr;
            }
        } else if (targetType==TYPE_FLOAT){
            if (sourceValue.type==TYPE_INT){
                targetValue->set_float(sourceValue.int_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_FLOAT){
                std::cout<<"sourceValue.float_val: "<<sourceValue.float_val<<std::endl;
                
                targetValue->set_float(sourceValue.float_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_BIGINT){
                targetValue->set_float(sourceValue.bigint_val);
                return targetValue;
            } else {
                return nullptr;
            }
        } else if (targetType==TYPE_BIGINT){
            if (sourceValue.type==TYPE_INT){
                targetValue->set_bigint(sourceValue.int_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_FLOAT){
                targetValue->set_bigint(sourceValue.float_val);
                return targetValue;
            } else if (sourceValue.type==TYPE_BIGINT){
                targetValue->set_bigint(sourceValue.bigint_val);
                return targetValue;
            } else {
                return nullptr;
            }
        } else if (targetType==TYPE_STRING){
            if (sourceValue.type==TYPE_STRING){
                targetValue->set_string(sourceValue.str_val);
                return targetValue;
            } else {
                return nullptr;
            }
        } else if (targetType==TYPE_DATETIME){
            if (sourceValue.type==TYPE_DATETIME){
                targetValue->set_datetime(sourceValue.datetime_val);
                return targetValue;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }
};