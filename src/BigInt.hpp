#pragma once
#include <csdtint>
#include <string>
#include "Base.hpp"

using cstdint::uint32_t;



class BigInt {
private:
    uint32_t* digits; 
    static const number_of_digits = 64;
    
    void BigInt_bin(std::string bin);
    void BigInt_oct(std::string oct);
    void BigInt_dec(std::string dec);
    void BigInt_hex(std::string hex);  
    void remove_leading_zeroes(std::string& number);
public:
    //constructors
    BigInt();
    BigInt(BigInt const& another);
    BigInt(std::string number, BASE base);
    BigInt(uint32_t one_digit_number);
    ~BigInt();

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
    BigInt operator/ (BigInt const& another) const;
    BigInt operator% (BigInt const& another) const;

    bool operator== (BigInt const& another) const;
    bool operator< (BigInt const& another) const;
    bool operator> (BigInt const& another) const;
    bool operator<= (BigInt const& another) const;
    bool operator>= (BigInt const& another) const;

};  