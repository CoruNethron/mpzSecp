#pragma once

#include <gmp.h>

class Mpz;

#define un_op_decl(T, O) \
    T& operator O()

#define un_bin_op_decl(T, O, A)               \
    T& operator A(const T& rhs);              \
    friend T operator O (T lhs, const T& rhs)

#define un_op_def(T, O, F) \
T& T::operator O() {       \
    F(d, d);               \
    return *this;          \
}

#define bin_op_def(T, O, A)           \
T operator O (T lhs, const T& rhs) {  \
    lhs A rhs;                        \
    return lhs;                       \
}

#define assign_op_def(T, O, A, F)  \
T& T::operator A(const T& rhs) {   \
    F(d, d, rhs.d);                \
    return *this;                  \
}                                  \
bin_op_def(T, O, A)

class Mpz {
public:
    mpz_t d{};

    Mpz(const Mpz&);
    explicit Mpz(const mpz_t);
    explicit Mpz(unsigned long int);
    explicit Mpz(signed long int);
    explicit Mpz(const char*, int = 16);

    ~Mpz();

    bool operator==(const Mpz& rhs);

    Mpz& operator=(const Mpz& other);

    un_bin_op_decl(Mpz, +, +=);
    un_bin_op_decl(Mpz, -, -=);
    un_bin_op_decl(Mpz, *, *=);
    un_bin_op_decl(Mpz, %, %=);
    un_bin_op_decl(Mpz, /, /=);

    Mpz& operator >>=(const mp_bitcnt_t &rhs);
    friend Mpz operator >>(Mpz lhs, const mp_bitcnt_t &rhs);

    Mpz& operator <<=(const mp_bitcnt_t &rhs);
    friend Mpz operator <<(Mpz lhs, const mp_bitcnt_t &rhs);

    un_op_decl(Mpz, -);
    un_op_decl(Mpz, +);
};
