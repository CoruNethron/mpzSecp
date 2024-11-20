#include "ECPoint.h"

bool ECPoint::operator==(const ECPoint& rhs) const {
    return x == rhs.x && y == rhs.y;
}

/* ~~~ Double ~~~ */
ECPoint ECPoint::operator~() const {
    ECPoint r;
    r.y = x * x;
    r.y += r.y + r.y;
    r.y /= y + y;
    r.x = r.y * r.y - x - x;
    r.y = r.y * ( x - r.x ) - y;
    return r;
}
/* ~~~ Double ~~~ */

/* ~~~ Add ~~~ */
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
bin_op_def(ECPoint, +, +=)
/* ~~~ Add ~~~ */

/* ~~~ Mul ~~~ */
ECPoint& ECPoint::operator *=(const Mpz& scalar){
    ECPoint r;
    Mpz rhcp = scalar;
    for(;mpz_sgn(rhcp.d) && !(mpz_tstbit(rhcp.d, 0) && (r = (*this)).x.d[0]._mp_size);
        rhcp >>= 1ul,
        *this = ~*this);
    for(;mpz_sgn(rhcp.d);
        rhcp >>= 1ul,
        *this = ~*this) if(mpz_tstbit(rhcp.d, 0)) r += (*this);
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
/* ~~~ Mul ~~~ */
