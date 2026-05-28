#include "big_number.h"

BigNumber::BigNumber() {
    round_type_mpfr = MPFR_RNDN;
    round_type = static_cast<BigRounding>(MPFR_RNDN);
    mpfr_init2(big_num, 256);
}

BigNumber::BigNumber(const BigNumber &other) {
    this->round_type = other.round_type;
    this->round_type_mpfr = static_cast<mpfr_rnd_t>(this->round_type);

    mpfr_init2(this->big_num, other.get_precision());

    mpfr_set(this->big_num, other.big_num, this->round_type_mpfr);
}

BigNumber::~BigNumber() {
    mpfr_clear(big_num);
}
