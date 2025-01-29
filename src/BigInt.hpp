#pragma once
#include <cstdint>
#include <string>
#include "Base.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::uint32_t;



class BigInt {
private:
    uint32_t* digits; 
    static const int number_of_digits = 64;
    static const int w = 32;
    void BigInt_bin(std::string bin);
    void BigInt_oct(std::string oct);
    void BigInt_dec(std::string dec);
    void BigInt_hex(std::string hex);  
    void remove_leading_zeroes(std::string& number);
    int cmp(const BigInt& another) const;
    std::pair<BigInt, BigInt> divmod(BigInt const& another);
public:
    //constructors
    BigInt();
    BigInt(BigInt const& another);
    BigInt(std::string number, BASE base);
    BigInt(uint32_t one_digit_number);
    ~BigInt();

    //functions
    void print() const;

    //operators
    BigInt operator<< (uint32_t const& left) const;
    BigInt operator>> (uint32_t const& right) const;
    BigInt operator& (BigInt const& another) const;
    BigInt operator^ (BigInt const& another) const;
    BigInt operator| (BigInt const& another) const;

    BigInt& operator= (BigInt const& another);
    BigInt operator+ (BigInt const& another) const;
    BigInt operator- (BigInt const& another) const;
    BigInt operator* (BigInt const& another) const;
    BigInt operator* (uint32_t const& another) const;
    BigInt operator/ (BigInt const& another) const;
    BigInt operator% (BigInt const& another) const;

    bool operator== (BigInt const& another) const;
    bool operator< (BigInt const& another) const;
    bool operator> (BigInt const& another) const;
    bool operator<= (BigInt const& another) const;
    bool operator>= (BigInt const& another) const;

};  