#include "src/ECPoint.h"

const Mpz Modnum::m("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
//const Mpz Modnum::m("61", 10);

int main() {
    ECPoint x{};
    Mpz k("12345");

    x = k * x;

    x.x.print(10);
    x.y.print(10);

    return 0;
}
