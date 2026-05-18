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

    void set_value(const BigNumber &big);
    float get_dec() const;
    std::string get_scientific() const;

    // ============= Operator Overloads ============= //
    godot::Ref<BigNumber> operator_sub(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_add(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mul(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_div(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_pow(const godot::Variant &p_other) const;
    godot::Ref<BigNumber> operator_mod(const godot::Variant &p_other) const;

    godot::Ref<BigNumber> operator_lshift() const;
    godot::Ref<BigNumber> operator_rshift() const;
    godot::Ref<BigNumber> operator_and() const;
    godot::Ref<BigNumber> operator_xor() const;
    
    int compare(const godot::Ref<BigNumber> &p_other) const;
    bool is_equal(const godot::Ref<BigNumber> &p_other) const;
    bool operator_less_than(const godot::Ref<BigNumber> &p_other) const { return compare(p_other) < 0; }
    bool operator_greater_than(const godot::Ref<BigNumber> &p_other) const { return compare(p_other) > 0; }

    godot::Ref<BigNumber> operator_neg(const godot::Ref<BigNumber> &p_other) const;
    godot::Ref<BigNumber> operator_pos(const godot::Ref<BigNumber> &p_other) const;

private:
    mpfr_t big_num;
    BigRounding round_type;

};

