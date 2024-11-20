#pragma once

#include <gmp.h>

class Mpz;

#define un_op_decl(T, O)                       \
    T& operator O()

#define un_bin_op_decl_sub(T, U, O, A)         \
    T& operator A(const U& rhs);               \
    friend T operator O (T lhs, const U& rhs)

#define un_bin_op_decl(T, O, A)                \
    un_bin_op_decl_sub(T, T, O, A)

#define un_op_def(T, O, F)                     \
T& T::operator O() {                           \
    F(d, d);                                   \
    return *this;                              \
}

#define bin_op_def_sub(T, U, O, A)             \
T operator O (T lhs, const U& rhs) {           \
    lhs A rhs;                                 \
    return lhs;                                \
}

#define bin_op_def(T, O, A)                    \
    bin_op_def_sub(T, T, O, A)

#define assign_op_def_sub(T, U, O, A, F, G)    \
T& T::operator A(const U& rhs) {               \
    F(d, d, G);                                \
    return *this;                              \
}                                              \
bin_op_def_sub(T, U, O, A)

#define assign_op_def(T, O, A, F)              \
    assign_op_def_sub(T, T, O, A, F, rhs.d)

class Mpz {
public:
    mpz_t d{};

    Mpz(const Mpz&);
    explicit Mpz(const mpz_t);
    explicit Mpz(unsigned long int);
    explicit Mpz(signed long int);
    explicit Mpz(const char*, int = 16);

    ~Mpz();

    bool operator==(const Mpz& rhs) const;
    bool operator<(const Mpz& rhs) const;

    Mpz& operator=(const Mpz& other);

    un_bin_op_decl(Mpz, +, +=);
    un_bin_op_decl(Mpz, -, -=);
    un_bin_op_decl(Mpz, *, *=);
    un_bin_op_decl(Mpz, %, %=);
    un_bin_op_decl(Mpz, /, /=);

    un_bin_op_decl_sub(Mpz, mp_bitcnt_t, >>, >>=);
    un_bin_op_decl_sub(Mpz, mp_bitcnt_t, <<, <<=);

    un_op_decl(Mpz, -);
    un_op_decl(Mpz, +);

    int operator|(const Mpz& other) const; // legendre

    static const Mpz mpz_num[10];
};
