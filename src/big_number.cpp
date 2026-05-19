/*
*
*   This is a source code file implementing Big Number related methods
*   Depends on Big Number.h
*
*/
#include "big_number.h"
#include "mpfr_operations.h"

#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// ================== Helper Functions ================== //
bool is_BigNumber(const godot::Variant &p_other) {
    godot::Object *raw_obj = p_other;

    if (raw_obj != nullptr && raw_obj->get_class() == "BigNumber")
        return true;

    return false;
}

godot::Ref<BigNumber> BigNumber::execute_math_op( const godot::Variant &p_other, mpfr_obj_func op_obj, mpfr_si_func op_si, mpfr_d_func op_d ) const {
    godot::Ref<BigNumber> result;
    result.instantiate();
    mpfr_set_prec(result->big_num, mpfr_get_prec(this->big_num));

    mpfr_rnd_t mpfr_rounding = static_cast<mpfr_rnd_t>(this->round_type);
    Variant::Type other_type = p_other.get_type();

    if (other_type == godot::Variant::OBJECT) {
        godot::Object *raw_obj = p_other;

        if (is_BigNumber(p_other)) {
            BigNumber *other_num = godot::Object::cast_to<BigNumber>(raw_obj);
            op_obj(result->big_num, this->big_num, other_num->big_num, mpfr_rounding);

        } else {
            String missing_class = raw_obj->get_class();
            ERR_PRINT("Expected BigNumber, but received class type: " + missing_class);
        }
    }

    else if(other_type == godot::Variant::INT) {
        long val = p_other;
        op_si(result->big_num, this->big_num, val, mpfr_rounding);
    }

    else if(other_type == godot::Variant::FLOAT) {
        double val = p_other;
        op_d(result->big_num, this->big_num, val, mpfr_rounding);
    }

    else {
        ERR_PRINT("BigNumber::execute_math_op - Unsupported Variant type!");
        mpfr_set(result->big_num, this->big_num, mpfr_rounding);
    }

    return result;
    
}

// ============== Constructor / Destructor ============== //
BigNumber::BigNumber() {
    round_type = static_cast<BigRounding>(MPFR_RNDN);
    mpfr_init2(big_num, 256);
}

BigNumber::BigNumber(const BigNumber &other) {
    
}

BigNumber::~BigNumber() {
    mpfr_clear(big_num);
}

// =================== Member Methods =================== //
void BigNumber::set_precision(const int &precision) {
    mpfr_prec_round(big_num, precision, static_cast<mpfr_rnd_t>(round_type));
}

int BigNumber::get_precision() const {
    return mpfr_get_prec(big_num);
}

void BigNumber::set_round_type(const int &value) {
    round_type = static_cast<BigRounding>(value);
}

int BigNumber::get_round_type() const {
    return static_cast<int>(round_type);
}

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

// ========== Bind Member Methods / Properties ========== //
void BigNumber::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_precision", "value"), &BigNumber::set_precision);
    ClassDB::bind_method(D_METHOD("get_precision"), &BigNumber::get_precision);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "precision"), "set_precision", "get_precision");

    // add property rounding_type

    godot::ClassDB::bind_method(godot::D_METHOD("compare", "other"), &BigNumber::compare);
    godot::ClassDB::bind_method(godot::D_METHOD("_equal", "other"), &BigNumber::operator_is_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_not_equal", "other"), &BigNumber::operator_not_is_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_less", "other"), &BigNumber::operator_less_than);
    godot::ClassDB::bind_method(godot::D_METHOD("_less_equal", "other"), &BigNumber::operator_less_than_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_greater", "other"), &BigNumber::operator_greater_than);
    godot::ClassDB::bind_method(godot::D_METHOD("_greater_equal", "other"), &BigNumber::operator_greater_than_equal);

    godot::ClassDB::bind_method(godot::D_METHOD("_add", "other"), &BigNumber::operator_add);
    godot::ClassDB::bind_method(godot::D_METHOD("_sub", "other"), &BigNumber::operator_sub);
    godot::ClassDB::bind_method(godot::D_METHOD("_mul", "other"), &BigNumber::operator_mul);
    godot::ClassDB::bind_method(godot::D_METHOD("_div", "other"), &BigNumber::operator_div);
    godot::ClassDB::bind_method(godot::D_METHOD("_mod", "other"), &BigNumber::operator_mod);
    godot::ClassDB::bind_method(godot::D_METHOD("_pow", "other"), &BigNumber::operator_pow);

    godot::ClassDB::bind_method(godot::D_METHOD("_neg"), &BigNumber::operator_neg);
}
