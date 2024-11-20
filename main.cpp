#include "src/Modnum.h"

const Mpz Modnum::m("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");

int main() {
    Modnum a("79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    Modnum b("483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");
    Modnum c = b - a;
    c.print();
    b.print();
    a.print();
    return 0;
}
