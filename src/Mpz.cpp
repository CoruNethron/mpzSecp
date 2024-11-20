#include "Mpz.h"

Mpz::Mpz(const Mpz& b) {
    mpz_init_set(d, b.d);
}

Mpz::Mpz(const mpz_t b) {
    mpz_init_set(d, b);
}

Mpz::Mpz(const unsigned long int b) {
    mpz_init_set_ui(d, b);
}

Mpz::Mpz(const signed long int b) {
    mpz_init_set_si(d, b);
}

Mpz::Mpz(const char *const str, const int base) {
    mpz_init_set_str(d, str, base);
}

Mpz::Mpz(const char *const str) {
    mpz_init_set_str(d, str, 16);
}

Mpz& Mpz::operator=(const Mpz& other){
    if (this == &other) return *this;
    mpz_set(d, other.d);
    return *this;
}

Mpz& Mpz::operator+=(const Mpz& rhs) {
    mpz_add(d, d, rhs.d);
    return *this;
}

bin_op_def(Mpz, +, +=)

Mpz& Mpz::operator-=(const Mpz& rhs) {
    mpz_sub(d, d, rhs.d);
    return *this;
}

bin_op_def(Mpz, -, -=)

Mpz& Mpz::operator%=(const Mpz& rhs) {
    mpz_mod(d, d, rhs.d);
    return *this;
}

bin_op_def(Mpz, %, %=)

Mpz::~Mpz(){
    mpz_clear(d);
}
