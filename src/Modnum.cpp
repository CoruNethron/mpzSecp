#include "Modnum.h"
#include <iostream>

Modnum::Modnum(const char *src, int base) : Mpz(src, base) {
    Mpz::operator%=(m);
}

void Modnum::print(int base) {
    char* s = mpz_get_str(nullptr, base, d);
    std::cout << s << std::endl;
    free(s);
}

bool Modnum::operator==(const Modnum& rhs) {
    return d == rhs.d;
}

#define mod_assign_bin_op_def(D, B, O, A)  \
D& D::operator A(const D& rhs) {           \
    B::operator A(rhs);                    \
    B::operator%=(m);                      \
    return *this;                          \
} bin_op_def(D, O, A)

#define mod_un_op_def(D, B, O)  \
D& D::operator O() {            \
    B::operator O();            \
    B::operator%=(m);           \
    return *this;               \
}

Modnum& Modnum::operator /=(const Modnum& rhs) { \
    Mpz t(0ul);                                  \
    mpz_invert(t.d, rhs.d, m.d);                 \
    Mpz::operator *=(t);                    \
    Mpz::operator%=(m);                     \
    return *this;                                \
} bin_op_def(Modnum, /, /=)

mod_assign_bin_op_def(Modnum, Mpz, +, +=)
mod_assign_bin_op_def(Modnum, Mpz, -, -=)
mod_assign_bin_op_def(Modnum, Mpz, *, *=)

mod_un_op_def(Modnum, Mpz, -)
mod_un_op_def(Modnum, Mpz, +)
