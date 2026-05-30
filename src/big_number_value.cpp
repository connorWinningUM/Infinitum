#include "big_number.h"
#include <string>

namespace {
    const char *ILLION_NUMS[] = {
        "", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion",
        "septillion", "octillion", "nonillion", "decillion", "undecillion", "duodecillion", "tredecillion",
        "quattuordecillion", "quindecillion", "sexdecillion", "septendecillion", "octodecillion", "novemdecillion"
    };

    const char *SHORT_METRIC_NUMS[] = {
        "", "k", "M", "G", "T", "P", "E", "Z", "Y", "R", "Q", "V", "U", "Td", "S", "Ri", "Qx", "Pp", "O", "N", "Mi"
    };

    const char *NAMED_METRIC_NUMS[] = {
        "", "kilo", "mega", "giga", "tera", "peta", "exa", "zetta", "yotta", "ronna", "quetta",
        "vunda", "uda", "treda", "sorta", "rinta", "quexa", "pepta", "ocha", "nena", "ming"
    };

    const char *ALPHABET[] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
    };
}

void BigNumber::set_scale_names(const godot::PackedStringArray &p_scales) {
    scale_names = p_scales;
}

godot::PackedStringArray BigNumber::get_scale_names() const {
    return scale_names;
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

void BigNumber::set_value_si(const long &p_value) {
    mpfr_set_si(this->big_num, p_value, this->round_type_mpfr);
}

void BigNumber::set_value_str(const godot::String &p_str, const int &p_base) {
    std::string c_str = p_str.utf8().get_data();
    mpfr_set_str(big_num, c_str.c_str(), p_base, round_type_mpfr);
}

long BigNumber::get_as_int() {
    if (!fits_si()) {
        godot::UtilityFunctions::printerr("BigNumber: value exceeds the limits of a signed integer. Use get_arbitrary_int instead.");
    }
    return mpfr_get_si(big_num, round_type_mpfr);
}

double BigNumber::get_as_float() {
    return mpfr_get_d(big_num, round_type_mpfr);
}

godot::String BigNumber::get_as_str(int p_sig_digits, int p_base) const {
    mpfr_exp_t exp;
    char* raw = mpfr_get_str(nullptr, &exp, p_base, p_sig_digits, big_num, round_type_mpfr);

    if (raw == nullptr) {
        return godot::String("0");
    }

    std::string result(raw);
    mpfr_free_str(raw);

    // handle negative, we will add it back later
    bool negative = result[0] == '-';
    if (negative) result = result.substr(1);

    // insert decimal point at position exp
    if (exp <= 0) {
        result = "0." + std::string(-exp, '0') + result;

    } else if (exp >= (int)result.size()) {
        // whole number, pad with zeros
        result += std::string(exp - result.size(), '0');

    } else {
        // insert in the middle
        result.insert(exp, ".");
    }

    if (negative) result = "-" + result;

    return godot::String(result.c_str());
}
