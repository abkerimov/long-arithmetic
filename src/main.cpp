#include "BigInt.hpp"
#include "Base.hpp"


int main() {
    BigInt s("fffffffffffffffffffffffffffffffffff", HEX);
    s.print();
    return 0;
}