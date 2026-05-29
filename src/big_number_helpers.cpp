#include "big_number.h"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>

#include "utils.h"

using namespace godot;
using utils::is_BigNumber;

godot::Ref<BigNumber> BigNumber::execute_math_op( const godot::Variant &p_other, mpfr_obj_func op_obj, mpfr_si_func op_si, mpfr_d_func op_d ) const {
    godot::Ref<BigNumber> result;
    result.instantiate();
    mpfr_set_prec(result->big_num, this->get_precision());

    Variant::Type other_type = p_other.get_type();

    if (other_type == godot::Variant::OBJECT) {
        godot::Object *raw_obj = p_other;

        if (is_BigNumber(p_other)) {
            BigNumber *other_num = godot::Object::cast_to<BigNumber>(raw_obj);
            op_obj(result->big_num, this->big_num, other_num->big_num, round_type_mpfr);

        } else {
            String missing_class = raw_obj->get_class();
            ERR_PRINT("Expected BigNumber, but received class type: " + missing_class);
        }
    }

    else if(other_type == godot::Variant::INT) {
        long val = p_other;
        op_si(result->big_num, this->big_num, val, round_type_mpfr);
    }

    else if(other_type == godot::Variant::FLOAT) {
        double val = p_other;
        op_d(result->big_num, this->big_num, val, round_type_mpfr);
    }

    else {
        ERR_PRINT("BigNumber::execute_math_op - Unsupported Variant type!, supported types: float, int, BigNumber");
        mpfr_set(result->big_num, this->big_num, round_type_mpfr);
    }

    return result;
    
}
