#include <gmp.h>
#include <iostream>

#define un_bin_op_decl(T, O, A)           \
T& operator A(const T& rhs);              \
friend T operator O (T lhs, const T& rhs)

#define bin_op_def(T, O, A)           \
T operator O (T lhs, const T& rhs) {  \
    lhs A rhs;                        \
    return lhs;                       \
}

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

bin_op_def(Mpz, +, +=)

Mpz& Mpz::operator-=(const Mpz& rhs) {
    mpz_sub(d, d, rhs.d);
    return *this;
}

bin_op_def(Mpz, -, -=)

Mpz& Mpz::operator%=(const Mpz& rhs) {
    mpz_mod(d, d, rhs.d);
    return *this;
}

bin_op_def(Mpz, %, %=)

Mpz::~Mpz(){
    mpz_clear(d);
}

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

Modnum::Modnum(const char *src) : Mpz(src) {
    mpz_mod(d, d, m.d);
}

Modnum& Modnum::operator+=(const Modnum& rhs) {
    mpz_add(d, d, rhs.d);
    mpz_mod(d, d, m.d);
    return *this;
}

bin_op_def(Modnum, +, +=)

Modnum& Modnum::operator-=(const Modnum& rhs) {
    mpz_sub(d, d, rhs.d);
    mpz_mod(d, d, m.d);
    return *this;
}

bin_op_def(Modnum, -, -=)

void Modnum::print(int base) {
    char* s = mpz_get_str(nullptr, base, d);
    std::cout << s << std::endl;
    free(s);
}

void Modnum::print() {
    print(16);
}

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
