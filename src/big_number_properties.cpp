#include "big_number.h"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

void BigNumber::set_precision(const int &precision) {
    if (precision < MPFR_PREC_MIN || precision > MPFR_PREC_MAX) {
        godot::UtilityFunctions::printerr(
            "BigNumber: Precision ", precision, 
            " is out of bounds! Must be between ", (int64_t)MPFR_PREC_MIN, 
            " and ", (int64_t)MPFR_PREC_MAX
        );
        return;
    }

    mpfr_prec_round(big_num, precision, round_type_mpfr);
}

int BigNumber::get_precision() const {
    return mpfr_get_prec(big_num);
}

void BigNumber::set_round_type(const godot::String &value) {
    mpfr_rnd_t tmpVal = round_type_mpfr;
    if (value == "Nearest")             tmpVal = MPFR_RNDN;
    else if (value == "Toward Zero")    tmpVal = MPFR_RNDZ;
    else if (value == "Up")             tmpVal = MPFR_RNDU;
    else if (value == "Down")           tmpVal = MPFR_RNDD;
    else if (value == "Away From Zero") tmpVal = MPFR_RNDA;
    else {
        godot::UtilityFunctions::printerr(
            "Round Type: ", 
            value,
            " is not a valid rounding type! ",
            "Valid rounding types are \"Nearest\" \"Toward Zero\" \"Up\" \"Down\" \"Away From Zero\""
        );
        return;
    }

    round_type_mpfr = tmpVal;
    round_type_string = value;
}

godot::String BigNumber::get_round_type() const {
    return round_type_string;
}

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

void BigNumber::set_value_si(const int &p_value) {
    mpfr_set_si(this->big_num, p_value, this->round_type_mpfr);
}
