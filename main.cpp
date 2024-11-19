#include <gmp.h>
#include <iostream>

class Mpz {
public:
    mpz_t d;

    Mpz(const Mpz&);
    Mpz(const mpz_t);
    Mpz(const unsigned long int);
    Mpz(const signed long int);
    Mpz(const char *const str, const int base);
    Mpz(const char *const str);

    Mpz& operator=(const Mpz& other);

    Mpz& operator+=(const Mpz& rhs);
    friend Mpz operator+(Mpz lhs, const Mpz& rhs){
        lhs += rhs;
        return lhs;
    }

    Mpz& operator%=(const Mpz& rhs);
    friend Mpz operator%(Mpz lhs, const Mpz& rhs){ // ck template op
        lhs %= rhs;
        return lhs;
    }

    ~Mpz();
};

Mpz::Mpz(const Mpz& b) {
    mpz_init_set(d, b.d);
}

Mpz::Mpz(const mpz_t b) {
    mpz_init_set(d, b);
}

Mpz::Mpz(const unsigned long int b) {
    mpz_init_set_ui(d, b);
}

Mpz::Mpz(const signed long int b) {
    mpz_init_set_si(d, b);
}

Mpz::Mpz(const char *const str, const int base) {
    mpz_init_set_str(d, str, base);
}

Mpz::Mpz(const char *const str) {
    mpz_init_set_str(d, str, 16);
}

Mpz& Mpz::operator=(const Mpz& other){
    if (this == &other) return *this;
    mpz_set(d, other.d);
    return *this;
}

Mpz& Mpz::operator+=(const Mpz& rhs) {
    mpz_add(d, d, rhs.d);
    return *this;
}

Mpz& Mpz::operator%=(const Mpz& rhs) {
    mpz_mod(d, d, rhs.d);
    return *this;
}

Mpz::~Mpz(){
    mpz_clear(d);
}

//extern char const mod[] = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";

//template<const char * modval>
class Modnum : public Mpz {
public:
    const static Mpz m; // check destructor

    Modnum(const Mpz);

    Modnum& operator+=(const Modnum& rhs);
    friend Modnum operator+(Modnum lhs, const Modnum& rhs) {
        lhs += rhs;
        return lhs;
    }
};

//typedef Modnum<mod> secpModnum;

//template<> secpModnum::Modnum(const Mpz src) : Mpz(src) {
Modnum::Modnum(const Mpz src) : Mpz(src) {
    mpz_mod(d, d, m.d);
};

//template<> secpModnum& secpModnum::operator+=(const Modnum& rhs) {
Modnum& Modnum::operator+=(const Modnum& rhs) {
    mpz_add(d, d, rhs.d);
    mpz_mod(d, d, m.d);
    return *this;
}

const Mpz Modnum::m = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";

int main() {
    Modnum a("79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    Modnum b("483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");
    Modnum c = a + b;
    char* s = mpz_get_str(nullptr, 16, c.d);
    std::cout << s << std::endl;
    free(s);
    return 0;
}
