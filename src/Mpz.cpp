#include "Mpz.h"

// TODO: make it foo with caching // hashing
const Mpz Mpz::mpz_num[10] = {
        Mpz("0"),
        Mpz("1"),
        Mpz("2"),
        Mpz("3"),
        Mpz("4"),
        Mpz("5"),
        Mpz("6"),
        Mpz("7"),
        Mpz("8"),
        Mpz("9")
};

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

bool Mpz::operator==(const Mpz& rhs) const {
    return 0 == mpz_cmp(this->d, rhs.d);
}

bool Mpz::operator<(const Mpz& rhs) const {
    return -1 == mpz_cmp(this->d, rhs.d);
}

int Mpz::operator|(const Mpz& other) const {
    return mpz_legendre(this->d, other.d);
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
assign_op_def(Mpz, /, /=, mpz_fdiv_q)
assign_op_def(Mpz, %, %=, mpz_mod)
assign_op_def(Mpz, &, &=, mpz_and)

assign_op_def_sub(Mpz, mp_bitcnt_t, >>, >>=, mpz_tdiv_q_2exp, rhs)
assign_op_def_sub(Mpz, mp_bitcnt_t, <<, <<=, mpz_mul_2exp, rhs)

un_op_def(Mpz, -, mpz_neg)
un_op_def(Mpz, +, mpz_abs)
