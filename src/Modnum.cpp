#include "Modnum.h"
#include <iostream>

const Mpz Modnum::m("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");

// TODO: make it foo with caching // hashing
const Modnum Modnum::mod_num[10] = {
        Modnum("0"),
        Modnum("1"),
        Modnum("2"),
        Modnum("3"),
        Modnum("4"),
        Modnum("5"),
        Modnum("6"),
        Modnum("7"),
        Modnum("8"),
        Modnum("9")
};

Modnum::Modnum(const char *src, int base) : Mpz(src, base) {
    Mpz::operator%=(m);
}

void Modnum::print(int base) {
    char* s = mpz_get_str(nullptr, base, d);
    std::cout << s << std::endl;
    free(s);
}

bool Modnum::operator==(const Modnum& rhs) const {
    return 0 == mpz_cmp(this->d, rhs.d);
}

bool Modnum::operator!=(const Modnum& rhs) const {
    return !(*this == rhs);
}

mod_assign_bin_op_def(Modnum, Mpz, +, +=)
mod_assign_bin_op_def(Modnum, Mpz, -, -=)
mod_assign_bin_op_def(Modnum, Mpz, *, *=)
Modnum& Modnum::operator /=(const Modnum& rhs) {
    Mpz t(0ul);
    mpz_invert(t.d, rhs.d, m.d);
    Mpz::operator*=(t);
    Mpz::operator%=(m);
    return *this;
}
bin_op_def(Modnum, /, /=)

Modnum& Modnum::operator ^=(const Mpz& rhs) {
    mpz_powm(this->d, this->d, rhs.d, m.d);
    return *this;
}
bin_op_def_sub(Modnum, Mpz, ^, ^=)

Modnum &Modnum::operator>>=(const mp_bitcnt_t &rhs) {
    Mpz::operator>>=(rhs);
    return *this;
}
Modnum operator>>(Modnum lhs, const mp_bitcnt_t &rhs) {
    lhs >>= rhs;
    return lhs;
}

Modnum &Modnum::operator<<=(const mp_bitcnt_t &rhs) {
    Mpz::operator<<=(rhs);
    Mpz::operator%=(m);
    return *this;
}
Modnum operator<<(Modnum lhs, const mp_bitcnt_t &rhs) {
    lhs <<= rhs;
    return lhs;
}

mod_un_op_def(Modnum, Mpz, -)
mod_un_op_def(Modnum, Mpz, +)

int Modnum::operator!() const {
    return mpz_legendre(this->d, m.d);
}

Modnum Modnum::operator~() const {
    // if((1 != !*this) || ((m & mpz_num[3]) != mpz_num[3])) return mod_num[0];
    return (*this) ^ ( ( m + mpz_num[1] ) >> 2 );
}
