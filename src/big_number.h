/*
*
*   This header holds the main class of the Infinitum Library, BigNumber
*
*   Acts like a wrapper for the mpfr library
*   By default, rounds down; precision = 256b; 
*/
#pragma once
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <string>
#include <mpfr.h>

class BigNumber: public godot::RefCounted {
    GDCLASS(BigNumber, godot::RefCounted)

protected:
    static void _bind_methods();

public:
    // Alias the mpfr rounding type enum so that it can be properly exported
    // all values are aliased so we can assume they have the same value and can be used as such
    enum BigRounding {
        ROUND_NEAREST = MPFR_RNDN,
        ROUND_ZERO = MPFR_RNDZ,
        ROUND_UP = MPFR_RNDU,
        ROUND_DOWN = MPFR_RNDD,
        ROUND_AWAY = MPFR_RNDA
    };

    BigNumber();
    ~BigNumber();
    BigNumber(const BigNumber &other);

    void set_precision(const int &precision);
    int get_precision() const;

    void set_round_type(const int &value);
    int get_round_type() const;

    void set_value(const godot::Variant &p_other);
    void set_valuebig(const godot::Ref<BigNumber> &p_other);
    void set_valuef(const double &p_value);
    void set_valuesi(const int &p_value);

    float to_float() const;
    std::string to_scientific() const;

    // ============= Operator Overloads ============= //
    godot::Ref<BigNumber> operator_sub(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_add(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mul(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_div(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_pow(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mod(const godot::Variant &p_other) const;
    
    int compare(const godot::Ref<BigNumber> &p_other) const;
    bool operator_is_equal(const godot::Ref<BigNumber> &p_other) const;
    bool operator_not_is_equal(const godot::Ref<BigNumber> &p_other) const;
    bool operator_less_than(const godot::Variant &p_other) const;
    bool operator_less_than_equal(const godot::Variant &p_other) const;
    bool operator_greater_than(const godot::Variant &p_other) const;
    bool operator_greater_than_equal(const godot::Variant &p_other) const;

    godot::Ref<BigNumber> operator_neg() const;

private:
    mpfr_t big_num;
    BigRounding round_type;

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

