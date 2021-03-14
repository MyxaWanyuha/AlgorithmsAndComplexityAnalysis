#pragma once
#include <iostream>
#include <string>

class BigInt
{
public:
    static const BigInt Zero;

    // Constructors:
    BigInt();
    BigInt(const BigInt& num);
    BigInt(BigInt&& num) noexcept;
    BigInt(const std::string& num);
    BigInt(const int64_t num);
    BigInt(const int32_t num);
    BigInt(const char* num);

    // Assignment operators:
    BigInt& operator=(BigInt&& num) noexcept;
    BigInt& operator=(const BigInt& num);
    BigInt& operator=(const int64_t& num);
    BigInt& operator=(const std::string& num);

    // Unary arithmetic operators:
    BigInt operator+() const;   // unary +
    BigInt operator-() const;   // unary -

    // Binary arithmetic operators:
    friend BigInt operator+(const BigInt& left, const BigInt& right);
    friend BigInt operator-(const BigInt& left, const BigInt& right);
    friend BigInt operator*(const BigInt& left, const BigInt& right);
    friend BigInt operator/(const BigInt& left, const BigInt& right);
    friend BigInt operator%(const BigInt& left, const BigInt& right);

    // Arithmetic-assignment operators:
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator/=(const BigInt& other);
    BigInt& operator%=(const BigInt& other);

    // Increment and decrement operators:
    BigInt& operator++();   // pre-increment
    BigInt& operator--();   // pre-decrement
    BigInt operator++(int); // post-increment
    BigInt operator--(int); // post-decrement

    // Relational operators:
    friend bool operator<  (const BigInt& left, const BigInt& right);
    friend bool operator>  (const BigInt& left, const BigInt& right);
    friend bool operator<= (const BigInt& left, const BigInt& right);
    friend bool operator>= (const BigInt& left, const BigInt& right);
    friend bool operator== (const BigInt& left, const BigInt& right);
    friend bool operator!= (const BigInt& left, const BigInt& right);

    // I/O stream operators:
    friend std::istream& operator>>(std::istream& in, BigInt& num);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);

    // Conversion functions:
    std::string ToString() const;
    int64_t ToInt64() const;

    // Math functions:
    static BigInt Pow(const BigInt& base, int64_t exp);
    bool IsPrime() const;
    // computes the inverse of a modulo n 
    static BigInt InverseOfModuloN(const BigInt& a, const BigInt& n);

private:
	std::string value = "0";
	char sign = '+';
    void ConstructFromString(const std::string& num);
    static void ExtendedEuclid(BigInt a, BigInt b, BigInt* x, BigInt* y, BigInt* d);
};
