#pragma once

#include <gmp.h>
#include "Utils.h"

class Mpz;

class Mpz {
public:
    mpz_t d{};

    Mpz(const Mpz&);
    explicit Mpz(const mpz_t);
    explicit Mpz(unsigned long int);
    explicit Mpz(signed long int);
    Mpz(const char * str, int base);
    explicit Mpz(const char *str);

    Mpz& operator=(const Mpz& other);

    un_bin_op_decl(Mpz, +, +=);
    un_bin_op_decl(Mpz, -, -=);
    un_bin_op_decl(Mpz, %, %=);

    ~Mpz();
};
