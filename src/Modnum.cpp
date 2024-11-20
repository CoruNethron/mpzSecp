#include "Modnum.h"
#include <iostream>

Modnum::Modnum(const char *src) : Mpz(src) {
    Mpz::operator%=(m);
}

#define mod_assign_op_def(D, B, O, A)  \
D& D::operator A(const D& rhs) {       \
    B::operator A(rhs);                \
    B::operator%=(m);                  \
    return *this;                      \
 } bin_op_def(D, O, A)

mod_assign_op_def(Modnum, Mpz, +, +=)

mod_assign_op_def(Modnum, Mpz, -, -=)

void Modnum::print(int base) {
    char* s = mpz_get_str(nullptr, base, d);
    std::cout << s << std::endl;
    free(s);
}
