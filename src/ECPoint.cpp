#include "ECPoint.h"

bool ECPoint::operator==(const ECPoint& rhs) {
    return x == rhs.x && y == rhs.y;
}

ECPoint ECPoint::operator~() const {
    ECPoint r;
    r.y = x * x;
    r.y += r.y + r.y;
    r.y /= y + y;
    r.x = r.y * r.y - x - x;
    r.y = r.y * ( x - r.x ) - y;
    return r;
}

ECPoint& ECPoint::operator +=(const ECPoint& rhs) {
    if( *this == rhs ) *this = ~*this;
    else if( this->x == rhs.x ) y = -y;
    else {
        Modnum s = ( y - rhs.y ) / ( x - rhs.x );
        x = s * s - x - rhs.x;
        y = s * ( rhs.x - x ) - rhs.y;
    }
    return *this;
}

ECPoint operator+(ECPoint lhs, const ECPoint& rhs) {
    lhs += rhs;
    return lhs;
}

ECPoint& ECPoint::operator *=(const Mpz& rhs){
    bool assigned = false;
    ECPoint r;
    Mpz rhcp = rhs;
    while(mpz_sgn(rhcp.d)) {
        if(mpz_tstbit(rhcp.d, 0)) {
            if (assigned) {
                r += (*this);
            } else {
                r = (*this);
                assigned = true;
            }
        }
        rhcp >>= 1ul;
        *this = ~*this;
    }
    *this = r;
    return *this;
}

ECPoint ECPoint::operator*(const Mpz& scalar) {
    *this *= scalar;
    return *this;
}

ECPoint operator*(const Mpz& scalar, ECPoint& rhs) {
    return rhs * scalar;
}
