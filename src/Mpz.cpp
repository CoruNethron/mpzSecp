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

Mpz::~Mpz(){
    mpz_clear(d);
}

bool Mpz::operator==(const Mpz& rhs) {
    return 0 == mpz_cmp(this->d, rhs.d);
}

// TODO: ck copy vs move assignment
Mpz& Mpz::operator=(const Mpz& other){
    if (this == &other) return *this;
    mpz_set(d, other.d);
    return *this;
}

assign_op_def(Mpz, +, +=, mpz_add)
assign_op_def(Mpz, -, -=, mpz_sub)
assign_op_def(Mpz, *, *=, mpz_mul)
assign_op_def(Mpz, %, %=, mpz_mod)
assign_op_def(Mpz, /, /=, mpz_fdiv_q)

Mpz &Mpz::operator>>=(const mp_bitcnt_t &rhs) {
    mpz_tdiv_q_2exp(d, d, rhs);
    return *this;
}
Mpz operator>>(Mpz lhs, const mp_bitcnt_t &rhs) {
    lhs >>= rhs;
    return lhs;
}

Mpz &Mpz::operator<<=(const mp_bitcnt_t &rhs) {
    mpz_mul_2exp(d, d, rhs);
    return *this;
}
Mpz operator<<(Mpz lhs, const mp_bitcnt_t &rhs) {
    lhs <<= rhs;
    return lhs;
}

un_op_def(Mpz, -, mpz_neg)
un_op_def(Mpz, +, mpz_abs)
