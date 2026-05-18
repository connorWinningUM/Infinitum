/*
*
*   This is a source code file implementing Big Number related methods
*   Depends on Big Number.h
*
*/
#include "big_number.h"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

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

bool BigNumber::is_equal(const godot::Ref<BigNumber> &p_other) const {
    if (p_other.is_null()) {
        return false;
    }
    return mpfr_cmp(this->big_num, p_other->big_num) == 0;
}

godot::Ref<BigNumber> operator_sub(const godot::Variant &p_other){
    
}
godot::Ref<BigNumber> operator_add(const godot::Variant &p_other){

}
godot::Ref<BigNumber> operator_mul(const godot::Variant &p_other){

}
godot::Ref<BigNumber> operator_div(const godot::Variant &p_other){

}
godot::Ref<BigNumber> operator_pow(const godot::Variant &p_other){

}
godot::Ref<BigNumber> operator_mod(const godot::Variant &p_other){

}



// ========== Bind Member Methods / Properties ========== //
void BigNumber::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_precision", "value"), &BigNumber::set_precision);
    ClassDB::bind_method(D_METHOD("get_precision"), &BigNumber::get_precision);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "precision"), "set_precision", "get_precision");

    // add property rounding_type

    godot::ClassDB::bind_method(godot::D_METHOD("compare", "other"), &BigNumber::compare);
    godot::ClassDB::bind_method(godot::D_METHOD("is_equal", "other"), &BigNumber::is_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_less", "other"), &BigNumber::operator_less_than);
    godot::ClassDB::bind_method(godot::D_METHOD("_greater", "other"), &BigNumber::operator_greater_than);



}
