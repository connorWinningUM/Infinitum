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
    void set_value_si(const int &p_value);


    // ============= Operator Overloads ============= //
public:    
    int compare(const godot::Ref<BigNumber> &p_other) const;

    bool operator_is_equal(const godot::Ref<BigNumber> &p_other) const;
    bool operator_not_is_equal(const godot::Ref<BigNumber> &p_other) const;
    //godot::Ref<BigNumber> operator_neg() const;

    /*
    bool lt_big(const BigNumber &p_other) const;
    bool lt_int(const int64_t &p_other) const;
    bool lt_f(const double &p_other) const;
    bool lte_big(const BigNumber &p_other) const;
    bool lte_int(const int64_t &p_other) const;
    bool lte_f(const double &p_other) const;
    bool gt_big(const BigNumber &p_other) const;
    bool gt_int(const int64_t &p_other) const;
    bool gt_f(const double &p_other) const;
    bool gte_big(const BigNumber &p_other) const;
    bool gte_int(const int64_t &p_other) const;
    bool gte_f(const double &p_other) const;

    godot::Ref<BigNumber> sub_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> sub_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> sub_f(const double &p_other) const;
    godot::Ref<BigNumber> add_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> add_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> add_f(const double &p_other) const;
    godot::Ref<BigNumber> mul_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> mul_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> mul_f(const double &p_other) const;
    godot::Ref<BigNumber> div_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> div_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> div_f(const double &p_other) const;
    godot::Ref<BigNumber> pow_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> pow_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> pow_f(const double &p_other) const;
    godot::Ref<BigNumber> mod_big(const BigNumber &p_other) const;
    godot::Ref<BigNumber> mod_int(const int64_t &p_other) const;
    godot::Ref<BigNumber> mod_f(const double &p_other) const;
    */

    // Godot doesnt allow operator overloading, so we must
    // create wrappers to call the operator methods
    // ============= Operator Wrappers ============== //
public: 
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


    // ================= Conversions ================ //
public:
    //long int get_as_int();
    //double get_as_float();
    //godot::String get_as_sci();
    

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
