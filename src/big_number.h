/*
*
*   This header holds the main class of the Infinitum Library, BigNumber
*
*   Acts like a wrapper for the mpfr library
*   By default, rounds down; precision = 256b; 
*/
#pragma once
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <mpfr.h>

class BigNumber: public godot::Resource {
    GDCLASS(BigNumber, godot::Resource)

protected:
    static void _bind_methods();
    static void _bind_rounding();
    static void _bind_precision();
    static void _bind_set_value();
    static void _bind_get_value();
    static void _bind_comparisons();
    static void _bind_operators();

public:
    BigNumber();
    ~BigNumber();
    BigNumber(const BigNumber &other);

    // ================= Properties ================= //
public:
    void set_precision(const int &precision);
    int get_precision() const;

    void set_round_type(const godot::String &value);
    godot::String get_round_type() const;

    void set_value_big(const godot::Ref<BigNumber> &p_other);
    void set_value_f(const double &p_value);
    void set_value_si(const long &p_value);
    void set_value_str(const godot::String &p_str, const int &p_base = 10);


    // ============= Operator Overloads ============= //
public:    
    int compare(const godot::Ref<BigNumber> &p_other) const;

    bool operator_is_equal(const godot::Ref<BigNumber> &p_other) const;
    bool operator_not_is_equal(const godot::Ref<BigNumber> &p_other) const;

    bool operator_less_than(const godot::Variant &p_other) const;
    //bool operator_less_than_equal(const godot::Variant &p_other) const;
    //bool operator_greater_than(const godot::Variant &p_other) const;
    //bool operator_greater_than_equal(const godot::Variant &p_other) const;

    godot::Ref<BigNumber> operator_sub(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_add(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mul(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_div(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_pow(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mod(const godot::Variant &p_other) const;

    //godot::Ref<BigNumber> operator_neg();

    // ================= Conversions ================ //
public:
    long get_as_int();
    double get_as_float();
    //godot::String get_as_sci();
    godot::String get_as_str();
    

    // ==================== Misc. =================== //
public:
    int sign() const;


private:
    mpfr_t big_num;
    mpfr_rnd_t round_type_mpfr;
    godot::String round_type_string;

    // function signature shapes MPFR uses for operations (used for the execute_math_op helper)
    typedef int (*mpfr_obj_func)(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);
    typedef int (*mpfr_si_func) (mpfr_ptr, mpfr_srcptr, long, mpfr_rnd_t);
    typedef int (*mpfr_d_func)  (mpfr_ptr, mpfr_srcptr, double, mpfr_rnd_t);

    // helper function which reduces repeated code in arithmetic operations
    godot::Ref<BigNumber> execute_math_op(
        const godot::Variant &p_other,
        mpfr_obj_func op_obj,
        mpfr_si_func op_si,
        mpfr_d_func op_d
    ) const;

};
