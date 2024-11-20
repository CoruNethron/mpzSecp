#include "Modnum.h"
#include <iostream>

Modnum::Modnum(const char *src) : Mpz(src) {
    mpz_mod(d, d, m.d);
}

Modnum& Modnum::operator+=(const Modnum& rhs) {
    mpz_add(d, d, rhs.d);
    mpz_mod(d, d, m.d);
    return *this;
}

bin_op_def(Modnum, +, +=)

Modnum& Modnum::operator-=(const Modnum& rhs) {
    mpz_sub(d, d, rhs.d);
    mpz_mod(d, d, m.d);
    return *this;
}

bin_op_def(Modnum, -, -=)

void Modnum::print(int base) {
    char* s = mpz_get_str(nullptr, base, d);
    std::cout << s << std::endl;
    free(s);
}

void Modnum::print() {
    print(16);
}
