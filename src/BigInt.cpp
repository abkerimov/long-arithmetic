#include "BigInt.hpp"
#include "Base.hpp"


BigInt::BigInt() {
    digits = new uint32_t[BigInt::number_of_digits]();
}

BigInt::BigInt(BigInt const& another) {
    digits = new uint32_t[BigInt::number_of_digits];
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        this->digits[i] = another.digits[i];
    }
}

BigInt::BigInt(std::string number, BASE base) {
    digits = new uint32_t[BigInt::number_of_digits](); // Initialize with zeros

    BigInt_hex(number);

    // switch (base) {
    //     case BIN:
    //         this->BigInt_bin(number);
    //         break;
    //     case OCT:
    //         this->BigInt_oct(number);
    //         break;
    //     case DEC:
    //         this->BigInt_dec(number);
    //         break;
    //     case HEX:
    //         this->BigInt_hex(number);
    //         break;
    //     default:
    //         throw std::invalid_argument("Invalid BASE value");
    // }
}

BigInt::BigInt(uint32_t one_digit_number) {
    digits = new uint32_t[BigInt::number_of_digits]();
    digits[0] = one_digit_number;
}

void BigInt::print() const{
    for (int i = 0; i < BigInt::number_of_digits; ++i) {
        std::cout << digits[i] << std::endl;
    }
}

void BigInt::remove_leading_zeroes(std::string& number) {
    size_t first_non_zero = number.find_first_not_of('0');
    number = (first_non_zero == std::string::npos) ? "0" : number.substr(first_non_zero);
}

void BigInt::BigInt_hex(std::string hex) {
    remove_leading_zeroes(hex);
    if (hex.empty()) {
        throw std::invalid_argument("Hex string is empty after removing leading zeroes.");
    }

    size_t hex_length = hex.length();
    if (hex_length > 512) { 
        throw std::invalid_argument("Hex string represents a number larger than 2048 bits.");
    }


    size_t chunk_index = 0;
    uint32_t accum = 0;
    size_t count = 0;

    for (size_t i = hex_length; i > 0; --i) {
        char hex_char = hex[i - 1];
        uint32_t hex_value = 0;

        if (hex_char >= '0' && hex_char <= '9') {
            hex_value = hex_char - '0';
        } else if (hex_char >= 'A' && hex_char <= 'F') {
            hex_value = hex_char - 'A' + 10;
        } else if (hex_char >= 'a' && hex_char <= 'f') {
            hex_value = hex_char - 'a' + 10;
        } else {
            throw std::invalid_argument("Invalid character in hex string.");
        }

        // Shift and accumulate
        accum |= (hex_value << (count * 4));
        count++;

        // Write to digits every 8 hex digits or at the last character
        if (count == 8 || i == 1) {
            digits[chunk_index++] = accum;
            count = 0;
            accum = 0;
        }
    }
}

BigInt::~BigInt() {
    delete[] digits;
    digits = nullptr; 
}

BigInt BigInt::operator+(BigInt const& another) const{
    uint32_t carry = 0;
    uint64_t temp;
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        temp = this->digits[i] + another.digits[i] + carry;
        result.digits[i] = temp & (1u<<BigInt::w - 1);
        carry = temp >> BigInt::w;
    }
    return result;
}

BigInt BigInt::operator-(BigInt const& another) const{
    uint32_t borrow = 0;
    long long temp;
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        temp = this->digits[i] - another.digits[i] - borrow;
        if (temp >= 0) {
            result.digits[i] = temp;
            borrow = 0;
        }
        else {
            result.digits[i] = (1u << BigInt::w ) + temp;
            borrow = 1;
        }
    }
    return result;
}

int BigInt::cmp(const BigInt& another) const {
    int i = BigInt::number_of_digits - 1;
    while (this->digits[i] == another.digits[i]) {
        --i;
    }
    if (i == -1) {
        return 0;
    }
    else {
        if (this->digits[i] > another.digits[i]) {
            return 1;
        }
        else {
            return -1;
        }
    }
}

bool BigInt::operator==(const BigInt& another) const {
    return (this->cmp(another) == 0);
}

bool BigInt::operator<(const BigInt& another) const {
    return (this->cmp(another) == -1);
}

bool BigInt::operator>(const BigInt& another) const {
    return (this->cmp(another) == 1);
}

bool BigInt::operator<=(const BigInt& another) const {
    return *this < another || *this == another;
}

bool BigInt::operator>=(const BigInt& another) const {
    return *this > another || *this == another;
}

BigInt BigInt::operator<<(uint32_t const& left) const {
    // operator is for bigendian notation, so it will look like this [1, 0, 0, ...] -> [0, 1, 0, ...]
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits - left; ++i) {
        result.digits[i+left] = this->digits[i];
    }
    return result;
}

BigInt BigInt::operator>>(uint32_t const& right) const {
    // operator is for bigendian notation, so it will look like this [0, 1, 0, ...] -> [1, 0, 0, ...]
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits - right; ++i) {
        result.digits[i] = this->digits[i + right];
    }
    return result;
}

BigInt BigInt::operator&(BigInt const& another) {
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        result.digits[i] = this->digits[i] & another.digits[i];
    }
    return result;
}

BigInt BigInt::operator|(BigInt const& another) {
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        result.digits[i] = this->digits[i] | another.digits[i];
    }
    return result;
}


BigInt BigInt::operator^(BigInt const& another) {
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        result.digits[i] = this->digits[i] ^ another.digits[i];
    }
    return result;
}

BigInt BigInt::operator*(uint32_t const& one_digit) {
    uint32_t carry = 0;
    BigInt result;
    for (size_t i = 0; i < BigInteger::number_of_digits; ++i) {
        uint64_t temp = this->digits[i] * one_digit + carry;
        result[i] = temp & (1u << BigInt::w - 1) 
    }
}

BigInt BigInt::operator*(BigInt const& another) {
    BigInt result;
    for (size_t i = 0; i < BigInt::number_of_digits; ++i) {
        BigInt temp = *this * another[i];
        temp = temp << i;
        result = result + temp;
    }
    return result;
}

std::pair<BigInt, BigInt> divmod(const BigInt& another) {
    
}

// void BigInt::BigInt_bin(std::string bin) {
//     // bin string is written in big-endian system
//     remove_leading_zeroes(bin);
//     if (bin.empty()) {
//         throw std::invalid_argument("Binary string is empty after removing leading zeroes.");
//     }

//     size_t bin_length = bin.length();
//     if (bin_length > 2048) {
//         throw std::invalid_argument("Binary string is too long, up to 2048 bits only.");
//     }

//     size_t num_chunks = (bin_length + 31) / 32;

//     if (!digits) {
//         digits = new uint32_t[num_chunks](); 
//     }

//     std::fill(digits, digits + num_chunks, 0); 

//     uint32_t accum = 0;
//     size_t count = 0;
//     size_t chunk_index = 0; 

//     for (size_t i = bin_length; i > 0; --i) { 
//         if (bin[i - 1] == '1') { 
//             accum |= (1U << count); 
//         }
//         count++;
//         if (count == 32 || i == 1) {
//             digits[chunk_index] = accum;
//             chunk_index++;
//             count = 0;
//             accum = 0;
//         }
//     }
// }

// void BigInt::BigInt_oct(std::string oct) {
//     // octal string is written in big-endian system
//     remove_leading_zeroes(oct);

//     if (bin.empty()) {
//         throw std::invalid_argument("Binary string is empty after removing leading zeroes.");
//     }

//     size_t bin_length = bin.length();
//     if (bin_length > 2048) {
//         throw std::invalid_argument("Binary string is too long, up to 2048 bits only.");
//     }
// }