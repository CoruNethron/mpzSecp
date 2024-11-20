#pragma once

#include <utility>

#include "Modnum.h"

class ECPoint;

class ECPoint {
public:
    Modnum x;
    Modnum y;

    // TODO: init by curve, from main, wno default
    explicit ECPoint(Modnum _x = Modnum("79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"),
                     Modnum _y = Modnum("483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8")) :
                     x(std::move(_x)), y(std::move(_y)) {}

    bool operator==(const ECPoint& rhs) const;

    ECPoint operator ~() const; // Double

    un_bin_op_decl(ECPoint, +, +=);

    ECPoint& operator *=(const Mpz& rhs);
    ECPoint operator*(const Mpz& scalar);
    friend ECPoint operator *(const Mpz& scalar, ECPoint& rhs);
};
