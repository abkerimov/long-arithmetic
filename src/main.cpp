#include "BigInt.hpp"
#include "Base.hpp"


int main() {
    BigInt s("fffffffffffffffffffffffffffffffffff", HEX);
    BigInt one(1u);
    s.print();
    one.print();
    BigInt sm1 = s - one;
    sm1.print();
    std::cout << "----------" << std::endl;
    std::cout << (s <= one) << std::endl;
    std::cout <<  (s == one) << std::endl;
    std::cout <<  (s >= one) << std::endl;
    std::cout <<  (s < one) << std::endl;
    std::cout <<  (s > one) << std::endl;
    std::cout << "----------" << std::endl;
    BigInt x = s << 1;
    x.print();
    return 0;
}