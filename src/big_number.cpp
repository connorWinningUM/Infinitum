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

void BigNumber::_bind_methods() {
    _bind_precision();
    _bind_rounding();
    _bind_set_value();
    _bind_get_value();
    _bind_comparisons();
    _bind_operators();
    _bind_misc();
}

void BigNumber::_bind_rounding() {
    ClassDB::bind_method(D_METHOD("set_rounding", "value"), &BigNumber::set_round_type);
    ClassDB::bind_method(D_METHOD("get_rounding"), &BigNumber::get_round_type);
    ADD_PROPERTY(
        PropertyInfo(
            Variant::STRING,                             
            "rounding",                                  
            PROPERTY_HINT_ENUM,                          
            "Nearest,Toward Zero,Up,Down,Away From Zero"
        ),
        "set_rounding",
        "get_rounding");
}

void BigNumber::_bind_precision() {
    ClassDB::bind_method(D_METHOD("set_precision", "value"), &BigNumber::set_precision);
    ClassDB::bind_method(D_METHOD("get_precision"), &BigNumber::get_precision);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "precision"), "set_precision", "get_precision");
}

void BigNumber::_bind_set_value() {
    godot::ClassDB::bind_method(godot::D_METHOD("from_big", "other"), &BigNumber::set_value_big);
    godot::ClassDB::bind_method(godot::D_METHOD("from_float", "value"), &BigNumber::set_value_f);
    godot::ClassDB::bind_method(godot::D_METHOD("from_int", "value"), &BigNumber::set_value_si);
    godot::ClassDB::bind_method(godot::D_METHOD("from_str", "string value", "base"), &BigNumber::set_value_str, 10);
}

void BigNumber::_bind_get_value() {
    godot::ClassDB::bind_method(godot::D_METHOD("to_int"), &BigNumber::get_as_int);
    godot::ClassDB::bind_method(godot::D_METHOD("to_float"), &BigNumber::get_as_float);
    godot::ClassDB::bind_method(godot::D_METHOD("to_str", "sig_digits", "base"), &BigNumber::get_as_str, 10);
}

void BigNumber::_bind_comparisons() {
    godot::ClassDB::bind_method(godot::D_METHOD("compare", "other"), &BigNumber::compare);
    godot::ClassDB::bind_method(godot::D_METHOD("_equal", "other"), &BigNumber::operator_is_equal);
    godot::ClassDB::bind_method(godot::D_METHOD("_not_equal", "other"), &BigNumber::operator_not_is_equal);
    //godot::ClassDB::bind_method(godot::D_METHOD("_less", "other"), &BigNumber::operator_less_than);
    //godot::ClassDB::bind_method(godot::D_METHOD("_less_equal", "other"), &BigNumber::operator_less_than_equal);
    //godot::ClassDB::bind_method(godot::D_METHOD("_greater", "other"), &BigNumber::operator_greater_than);
    //godot::ClassDB::bind_method(godot::D_METHOD("_greater_equal", "other"), &BigNumber::operator_greater_than_equal);
}

void BigNumber::_bind_operators() {
    godot::ClassDB::bind_method(godot::D_METHOD("_add", "other"), &BigNumber::operator_add);
    godot::ClassDB::bind_method(godot::D_METHOD("_sub", "other"), &BigNumber::operator_sub);
    godot::ClassDB::bind_method(godot::D_METHOD("_mul", "other"), &BigNumber::operator_mul);
    godot::ClassDB::bind_method(godot::D_METHOD("_div", "other"), &BigNumber::operator_div);
    godot::ClassDB::bind_method(godot::D_METHOD("_mod", "other"), &BigNumber::operator_mod);
    godot::ClassDB::bind_method(godot::D_METHOD("_pow", "other"), &BigNumber::operator_pow);
}

void BigNumber::_bind_misc() {
    godot::ClassDB::bind_method(godot::D_METHOD("fits_int", "other"), &BigNumber::fits_si);
    ClassDB::bind_method(D_METHOD("set_scale_names", "names"), &BigNumber::set_scale_names);
    ClassDB::bind_method(D_METHOD("get_scale_names"), &BigNumber::get_scale_names);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "scale_names"), "set_scale_names", "get_scale_names");
}
