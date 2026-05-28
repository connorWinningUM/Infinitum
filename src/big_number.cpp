/*
*
*   This is a source code file implementing Big Number related methods
*   Depends on Big Number.h
*
*/
#include "big_number.h"
#include "mpfr_operations.h"
#include "utils.h"

#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
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
    Variant::Type other_type = p_other.get_type();
    godot::Object *raw_obj = p_other;

    if(other_type == godot::Variant::OBJECT) {
        if(is_BigNumber(other_type)){
            BigNumber *other_num = godot::Object::cast_to<BigNumber>(raw_obj);
            return mpfr_less_p(this->big_num, other_num->big_num);

        } else {
            String missing_class = raw_obj->get_class();
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

// returns positive value if the big_num is positive
// returns negative value otherwise
int BigNumber::sign() const {
    return mpfr_sgn(big_num);
}

// ========== Bind Member Methods / Properties ========== //
void BigNumber::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_precision", "value"), &BigNumber::set_precision);
    ClassDB::bind_method(D_METHOD("get_precision"), &BigNumber::get_precision);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "precision"), "set_precision", "get_precision");

    // add property rounding_type
    //ClassDB::bind_method(D_METHOD("set_rounding", "value"), &BigNumber::set_precision);

    godot::ClassDB::bind_method(godot::D_METHOD("set_value_big", "other"), &BigNumber::set_value_big);
    godot::ClassDB::bind_method(godot::D_METHOD("set_value_float", "value"), &BigNumber::set_value_f);
    godot::ClassDB::bind_method(godot::D_METHOD("set_value_int", "value"), &BigNumber::set_value_si);

    godot::ClassDB::bind_method(godot::D_METHOD("compare", "other"), &BigNumber::compare);
    godot::ClassDB::bind_method(godot::D_METHOD("_equal", "other"), &BigNumber::operator_is_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_not_equal", "other"), &BigNumber::operator_not_is_equal);
    //godot::ClassDB::bind_method(godot::D_METHOD("_less", "other"), &BigNumber::operator_less_than);
    //godot::ClassDB::bind_method(godot::D_METHOD("_less_equal", "other"), &BigNumber::operator_less_than_equal);
    //godot::ClassDB::bind_method(godot::D_METHOD("_greater", "other"), &BigNumber::operator_greater_than);
    //godot::ClassDB::bind_method(godot::D_METHOD("_greater_equal", "other"), &BigNumber::operator_greater_than_equal);

    godot::ClassDB::bind_method(godot::D_METHOD("_add", "other"), &BigNumber::operator_add);
    godot::ClassDB::bind_method(godot::D_METHOD("_sub", "other"), &BigNumber::operator_sub);
    godot::ClassDB::bind_method(godot::D_METHOD("_mul", "other"), &BigNumber::operator_mul);
    godot::ClassDB::bind_method(godot::D_METHOD("_div", "other"), &BigNumber::operator_div);
    godot::ClassDB::bind_method(godot::D_METHOD("_mod", "other"), &BigNumber::operator_mod);
    godot::ClassDB::bind_method(godot::D_METHOD("_pow", "other"), &BigNumber::operator_pow);

    //godot::ClassDB::bind_method(godot::D_METHOD("_neg"), &BigNumber::operator_neg);
}
