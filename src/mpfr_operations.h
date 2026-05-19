/*
*
*   This header holds functions for mpfr operations which dont exist in the mpfr library
*
*
*/
#include <mpfr.h>

inline int mpfr_pow_d(mpfr_ptr rop, mpfr_srcptr op1, double op2, mpfr_rnd_t rnd) {
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(op1));
    mpfr_set_d(temp, op2, rnd);
    
    int status = mpfr_pow(rop, op1, temp, rnd);
    
    mpfr_clear(temp);
    return status;
}

inline int mpfr_fmod_si(mpfr_ptr rop, mpfr_srcptr op1, long op2, mpfr_rnd_t rnd) {
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(op1));
    mpfr_set_si(temp, op2, rnd);
    
    int status = mpfr_fmod(rop, op1, temp, rnd);
    
    mpfr_clear(temp);
    return status;
}

inline int mpfr_fmod_d(mpfr_ptr rop, mpfr_srcptr op1, double op2, mpfr_rnd_t rnd) {
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(op1));
    mpfr_set_d(temp, op2, rnd);
    
    int status = mpfr_fmod(rop, op1, temp, rnd);
    
    mpfr_clear(temp);
    return status;
}
