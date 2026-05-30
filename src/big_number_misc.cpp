#include "big_number.h"

// returns positive value if the big_num is positive
// returns negative value otherwise
int BigNumber::sign() const {
    return mpfr_sgn(big_num);
}

bool BigNumber::fits_si() const {
    return mpfr_fits_slong_p(big_num, round_type_mpfr) != 0;
}
