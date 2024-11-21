#pragma once

#include "Mpz.h"

class Modnum;

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

class Modnum : public Mpz {
public:
    const static Mpz m;

    explicit Modnum(const char *, int = 16);

    void print(int = 16);

    cmp_op_decl(Modnum, ==, bool);           // equality
    cmp_op_decl(Modnum, !=, bool);           // non equality
    int operator!() const;                   // legendre symbol

    un_bin_op_decl(Modnum, +, +=);           // modular addition
    un_bin_op_decl(Modnum, -, -=);           // modular subtraction
    un_bin_op_decl(Modnum, *, *=);           // modular multiply
    un_bin_op_decl(Modnum, /, /=);           // multiply by modular multiplicative inverse
    un_bin_op_decl_sub(Modnum, Mpz, ^, ^=);  // modular power
    Modnum operator ~() const;               // modular square root

    un_bin_op_decl_sub(Modnum, mp_bitcnt_t, >>, >>=);  // right bit shift
    un_bin_op_decl_sub(Modnum, mp_bitcnt_t, <<, <<=);  // modular left bit shift

    un_op_decl(Modnum, -);                   // modular negation
    un_op_decl(Modnum, +);                   // absolute value

    static const Modnum mod_num[10];
};
