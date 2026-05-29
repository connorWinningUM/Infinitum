#include "big_number.h"
#include "utils.h"
#include "mpfr_operations.h"

using utils::is_BigNumber;

// ============= Operator Overloads ============= //

int BigNumber::compare(const godot::Ref<BigNumber> &p_other) const {
    if (p_other.is_null()) {
        return 1;
    }
    return mpfr_cmp(this->big_num, p_other->big_num);
}

bool BigNumber::operator_is_equal(const godot::Ref<BigNumber> &p_other) const {
    if (p_other.is_null()) {
        return false;
    }
    return mpfr_cmp(this->big_num, p_other->big_num) == 0;
}

bool BigNumber::operator_not_is_equal(const godot::Ref<BigNumber> &p_other) const {
    return !operator_is_equal(p_other);
}

// ============= Operator Wrappers ============== //

bool BigNumber::operator_less_than(const godot::Variant &p_other) const {
    godot::Variant::Type other_type = p_other.get_type();
    godot::Object *raw_obj = p_other;

    if(other_type == godot::Variant::OBJECT) {
        if(is_BigNumber(other_type)){
            BigNumber *other_num = godot::Object::cast_to<BigNumber>(raw_obj);
            return mpfr_less_p(this->big_num, other_num->big_num);

        } else {
            godot::String missing_class = raw_obj->get_class();
            ERR_PRINT("Expected BigNumber, but received class type: " + missing_class);
        }

    } else if(other_type == godot::Variant::INT) {
        

    } else if(other_type == godot::Variant::FLOAT) {


    } else {
        ERR_PRINT("BigNumber::execute_comparison - Unsupported Variant type!, supported types: float, int, BigNumber");
    }
    return false;
}

//bool BigNumber::operator_less_than_equal(const godot::Variant &p_other) const {}

//bool BigNumber::operator_greater_than(const godot::Variant &p_other) const {}

//bool BigNumber::operator_greater_than_equal(const godot::Variant &p_other) const {}

godot::Ref<BigNumber> BigNumber::operator_sub(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_sub, mpfr_sub_si, mpfr_sub_d);
}
godot::Ref<BigNumber> BigNumber::operator_add(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_sub, mpfr_sub_si, mpfr_sub_d);
}
godot::Ref<BigNumber> BigNumber::operator_mul(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_mul, mpfr_mul_si, mpfr_mul_d);
}
godot::Ref<BigNumber> BigNumber::operator_div(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_div, mpfr_div_si, mpfr_div_d);
}
godot::Ref<BigNumber> BigNumber::operator_mod(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_fmod, mpfr_fmod_si, mpfr_fmod_d);
}
godot::Ref<BigNumber> BigNumber::operator_pow(const godot::Variant &p_other) const {
    return execute_math_op(p_other, mpfr_pow, mpfr_pow_si, mpfr_pow_d);
}

//godot::Ref<BigNumber> BigNumber::operator_neg() const {}
