#pragma once

#include "Mpz.h"

class Modnum;

class Modnum : public Mpz {
public:
    const static Mpz m;

    explicit Modnum(const char *, int = 16);

    void print(int = 16);

    bool operator==(const Modnum& rhs);

    un_bin_op_decl(Modnum, +, +=);
    un_bin_op_decl(Modnum, -, -=);
    un_bin_op_decl(Modnum, *, *=);
    un_bin_op_decl(Modnum, /, /=);

    un_op_decl(Modnum, -);
    un_op_decl(Modnum, +);
};
