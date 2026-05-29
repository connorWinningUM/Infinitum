#include "big_number.h"

BigNumber::BigNumber() {
    round_type_mpfr = MPFR_RNDN;
    round_type_string = "Nearest";
    mpfr_init2(big_num, 256);
}

BigNumber::BigNumber(const BigNumber &other) {
    this->round_type_mpfr = other.round_type_mpfr;

    mpfr_init2(this->big_num, other.get_precision());

    mpfr_set(this->big_num, other.big_num, this->round_type_mpfr);
}

BigNumber::~BigNumber() {
    mpfr_clear(big_num);
}
