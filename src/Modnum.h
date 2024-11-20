#pragma once

#include "Mpz.h"

class Modnum;

class Modnum : public Mpz {
public:
    const static Mpz m; // check destructor

    explicit Modnum(const char *);

    un_bin_op_decl(Modnum, +, +=);
    un_bin_op_decl(Modnum, -, -=);

    void print(int);
    void print();
};