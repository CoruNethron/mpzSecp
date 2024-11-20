#pragma once

#include "Mpz.h"

class Modnum;

class Modnum : public Mpz {
public:
    const static Mpz m;

    explicit Modnum(const char *, int = 16);

    void print(int = 16);

    bool operator==(const Modnum& rhs) const;

    un_bin_op_decl(Modnum, +, +=);
    un_bin_op_decl(Modnum, -, -=);
    un_bin_op_decl(Modnum, *, *=);
    un_bin_op_decl(Modnum, /, /=);
    un_bin_op_decl_sub(Modnum, Mpz, ^, ^=);

    un_op_decl(Modnum, -);
    un_op_decl(Modnum, +);

    int operator!() const; // legendre

    Modnum operator ~() const; // msqrt

    static const Modnum mod_num[10];
};
