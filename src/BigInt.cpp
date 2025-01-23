#include "BigInt.hpp"
#include "Base.hpp"


BigInt::BigInt() {
    digits = new uint32_t[BigInt.number_of_digits]();
}

BigInt::BigInt(BigInt const& another) {
    digits = new uint32_t[BigInt.number_of_digits];
    for (size_t i = 0; i < BigInt.number_of_digits; ++i) {
        this->digits[i] = another.digits[i];
    }
}

BigInt::BigInt(std::string number, BASE base) {
    switch (base) {
        case BIN:
            this->BigInt_bin(number);
            break;
        case OCT:
            this->BigInt_oct(number);
            break;
        case DEC:
            this->BigInt_dec(number);
            break;
        case HEX:
            this->BigInt_hex(number);
            break;
        default:
            throw std::invalid_argument("Invalid BASE value");
    }
}

BigInt::BigInt(uint32_t one_digit_number) {
    digits = new uint32_t[BigInt.number_of_digits]();
    digits[0] = one_digit_number;
}

BigInt::~BigInt() {
    delete[] digits;
}

void BigInt::remove_leading_zeroes(std::string& number) {
    size_t first_non_zero = number.find_first_of('1');
    number = (first_non_zero == std::string::npos) ? "0" : number.substr(first_non_zero);
}

void BigInt::BigInt_bin(std::string bin) {
    // bin string is written in bigendian notation

    // not finished yet
    if (bin.length() > 2048) {
        throw std::invalid_argument("bin str is too long, up to 2048 bits only");
    }    
    remove_leading_zeroes(bin);
    uint32_t accum = 0;
    int c = 0;
    for (size_t i = bin.length() - 1; i >= 0; --i) {
        if (i % 32 == 0) {
            this->digits[c] = accum 
            accum = 0;
            c++;
        }
        accum += bin[i] * (2 << (32 - (i % 32)));
    }
}