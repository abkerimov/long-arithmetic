#include "BigInt.hpp"
#include "Base.hpp"


int main() {
    BigInt s("fffffffffffffffffffffffffffffffffff", HEX);
    BigInt one(1u);
    s.print();
    one.print();
    BigInt sm1 = s - one;
    sm1.print();
    return 0;
}