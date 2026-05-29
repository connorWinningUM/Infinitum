#include "big_number.h"

void BigNumber::set_value_big(const godot::Ref<BigNumber> &p_other) {
    if (p_other.is_null())
        return; 

    if (this == p_other.ptr())
        return;

    this->round_type_mpfr = p_other->round_type_mpfr;

    mpfr_prec_round(this->big_num, p_other->get_precision(), this->round_type_mpfr);
    mpfr_set(this->big_num, p_other->big_num, this->round_type_mpfr);
}

void BigNumber::set_value_f(const double &p_value) {
    mpfr_set_d(this->big_num, p_value, this->round_type_mpfr);
}

void BigNumber::set_value_si(const long &p_value) {
    mpfr_set_si(this->big_num, p_value, this->round_type_mpfr);
}

long BigNumber::get_as_int() {
    return mpfr_get_si(big_num, round_type_mpfr);
}
