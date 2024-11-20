#include "src/ECPoint.h"

const Mpz Modnum::m("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");

int main() {
    ECPoint G{};
    Mpz k("12345");

    //G *= k;

    G.x.print(16);
    G.y.print(16);

    Modnum x("79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    Modnum y = ~(x * x * x + Modnum::mod_num[7]);

    y.print();

    Modnum z = ~( G.x ^ Mpz::mpz_num[3] + Modnum::mod_num[7] );

    return 0;
}
