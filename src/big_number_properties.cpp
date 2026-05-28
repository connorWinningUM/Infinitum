#include "big_number.h"

void BigNumber::set_precision(const int &precision) {
    mpfr_prec_round(big_num, precision, static_cast<mpfr_rnd_t>(round_type));
}

int BigNumber::get_precision() const {
    return mpfr_get_prec(big_num);
}

void BigNumber::set_round_type(const int &value) {
    this->round_type = static_cast<BigRounding>(value);
    this->round_type_mpfr = static_cast<mpfr_rnd_t>(value);
}

int BigNumber::get_round_type() const {
    return static_cast<int>(round_type);
}

void BigNumber::set_value_big(const godot::Ref<BigNumber> &p_other) {
    if (p_other.is_null())
        return; 

    if (this == p_other.ptr())
        return;

    this->round_type = p_other->round_type;
    this->round_type_mpfr = static_cast<mpfr_rnd_t>(this->round_type);

    mpfr_prec_round(this->big_num, p_other->get_precision(), this->round_type_mpfr);
    mpfr_set(this->big_num, p_other->big_num, this->round_type_mpfr);
}

void BigNumber::set_value_f(const double &p_value) {
    mpfr_set_d(this->big_num, p_value, this->round_type_mpfr);
}

void BigNumber::set_value_si(const int &p_value) {
    mpfr_set_si(this->big_num, p_value, this->round_type_mpfr);
}
