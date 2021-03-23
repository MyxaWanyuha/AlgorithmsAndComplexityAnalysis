#include "BigInt.h"
#include <tuple>

const BigInt BigInt::Zero("0");

BigInt abs(const BigInt& num)
{
    return num < BigInt::Zero ? -num : num;
}

bool IsValidNumber(const std::string& num)
{
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;
    return true;
}

void StripLeadingZeros(std::string& num)
{
    size_t i;
    for (i = 0; i < num.size(); i++)
        if (num[i] != '0')
            break;

    if (i == num.size())
        num = "0";
    else
        num = num.substr(i);
}

void AddLeadingZeroes(std::string& num, size_t num_zeroes)
{
    num = std::string(num_zeroes, '0') + num;
}

void AddTrailingZeroes(std::string& num, size_t num_zeroes)
{
    num += std::string(num_zeroes, '0');
}

std::tuple<std::string, std::string> GetLargerAndSmaller(const std::string& num1, const std::string& num2)
{
    std::string larger, smaller;
    if (num1.size() > num2.size() || (num1.size() == num2.size() && num1 > num2))
    {
        larger = num1;
        smaller = num2;
    }
    else
    {
        larger = num2;
        smaller = num1;
    }

    AddLeadingZeroes(smaller, larger.size() - smaller.size());
    return std::make_tuple(larger, smaller);
}

bool IsPowerOf10(const std::string& num)
{
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;
    return true;
}

BigInt::BigInt()
    :value("0"), sign('+')
{
}

BigInt::BigInt(const BigInt& num)
    :value(num.value), sign(num.sign)
{
}

BigInt::BigInt(BigInt&& num) noexcept
    :value(std::move(num.value)), sign(std::move(num.sign))
{
}

BigInt::BigInt(const int64_t num)
    : value(std::to_string(std::abs(num))), sign(num < 0 ? '-' : '+')
{
}

BigInt::BigInt(const int32_t num)
    :BigInt(static_cast<int64_t>(num))
{
}

BigInt::BigInt(const std::string& num)
{
    ConstructFromString(num);
}

BigInt::BigInt(const char* num)
{
    ConstructFromString(num);
}

std::string BigInt::ToString() const
{
    return sign == '-' ? "-" + value : value;
}

void BigInt::ConstructFromString(const std::string& num)
{
    if (num.size() == 0) return;

    if (num[0] == '+' or num[0] == '-')
    {
        std::string magnitude = num.substr(1);
        if (IsValidNumber(magnitude))
        {
            value = magnitude;
            sign = num[0];
        }
        else
        {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    else // if no sign is specified
    {
        if (IsValidNumber(num))
        {
            value = num;
            sign = '+';
        }
        else
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
    }
    StripLeadingZeros(value);
}

BigInt& BigInt::operator=(BigInt&& num) noexcept
{
    value = std::move(num.value);
    sign = std::move(num.sign);
    return *this;
}

BigInt& BigInt::operator=(const BigInt& num)
{
    value = num.value;
    sign = num.sign;
    return *this;
}

BigInt& BigInt::operator=(const int64_t& num)
{
    BigInt temp(num);
    value = std::move(temp.value);
    sign = std::move(temp.sign);
    return *this;
}

BigInt& BigInt::operator=(const std::string& num)
{
    BigInt temp(num);
    value = std::move(temp.value);
    sign = std::move(temp.sign);
    return *this;
}

BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt temp(*this);
    if (value != "0")
        temp.sign = sign == '+' ? '-' : '+';
    return temp;
}

BigInt operator+(const BigInt& left, const BigInt& right)
{
    // if the operands are of opposite signs, perform subtraction
    if (left.sign == '+' && right.sign == '-')
    {
        BigInt rhs = right;
        rhs.sign = '+';
        return left - rhs;
    }
    else if (left.sign == '-' && right.sign == '+')
    {
        BigInt lhs = left;
        lhs.sign = '+';
        return -(lhs - right);
    }

    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    std::tie(larger, smaller) = GetLargerAndSmaller(left.value, right.value);

    BigInt sumResult;
    sumResult.value = ""; // the value is cleared as the digits will be appended
    short carry = 0, sum;
    // add the two values
    for (long i = larger.size() - 1; i >= 0; i--)
    {
        sum = larger[i] - '0' + smaller[i] - '0' + carry;
        sumResult.value = std::to_string(sum % 10) + sumResult.value;
        carry = sum / static_cast<short>(10);
    }

    if (carry)
    {
        sumResult.value = std::to_string(carry) + sumResult.value;
    }

    // if the operands are negative, the result is negative
    if (left.sign == '-' && sumResult.value != "0")
    {
        sumResult.sign = '-';
    }
    return sumResult;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
    // if the operands are of opposite signs, perform addition
    if (left.sign == '+' && right.sign == '-')
    {
        BigInt rhs = right;
        rhs.sign = '+';
        return left + rhs;
    }
    else if (left.sign == '-' && right.sign == '+')
    {
        BigInt lhs = left;
        lhs.sign = '+';
        return -(lhs + right);
    }

    BigInt differenceResult;
    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    if (abs(left) > abs(right))
    {
        larger = left.value;
        smaller = right.value;
        if (left.sign == '-')      // -larger - -smaller = -result
            differenceResult.sign = '-';
    }
    else
    {
        larger = right.value;
        smaller = left.value;
        if (right.sign == '+')        // smaller - larger = -result
            differenceResult.sign = '-';
    }
    // pad the smaller number with zeroes
    AddLeadingZeroes(smaller, larger.size() - smaller.size());

    differenceResult.value = "";  // the value is cleared as the digits will be appended
    short difference;
    long i, j;
    // subtract the two values
    for (i = larger.size() - 1; i >= 0; i--)
    {
        difference = larger[i] - smaller[i];
        if (difference < 0)
        {
            for (j = i - 1; j >= 0; j--)
            {
                if (larger[j] != '0')
                {
                    larger[j]--;    // borrow from the j-th digit
                    break;
                }
            }
            j++;
            while (j != i)
            {
                larger[j] = '9';    // add the borrow and take away 1
                j++;
            }
            difference += 10;   // add the borrow
        }
        differenceResult.value = std::to_string(difference) + differenceResult.value;
    }
    StripLeadingZeros(differenceResult.value);

    // if the result is 0, set its sign as +
    if (differenceResult.value == "0")
        differenceResult.sign = '+';

    return differenceResult;
}

BigInt operator*(const BigInt& left, const BigInt& right)
{
    if (left == BigInt::Zero or right == BigInt::Zero)
        return BigInt::Zero;
    if (left == 1)
        return right;
    if (right == 1)
        return left;

    BigInt product;

    const int64_t FLOOR_SQRT_LLONG_MAX = 3037000499;
    if (abs(left) <= FLOOR_SQRT_LLONG_MAX && abs(right) <= FLOOR_SQRT_LLONG_MAX)
    {
        product = std::stoll(left.value) * std::stoll(right.value);
    }
    else if (IsPowerOf10(left.value))
    { // if LHS is a power of 10 do optimised operation 
        product.value = right.value;
        product.value.append(left.value.begin() + 1, left.value.end());
    }
    else if (IsPowerOf10(right.value))
    { // if RHS is a power of 10 do optimised operation 
        product.value = left.value;
        product.value.append(right.value.begin() + 1, right.value.end());
    }
    else
    {
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = GetLargerAndSmaller(left.value, right.value);

        size_t half_length = larger.size() / 2;
        auto half_length_ceil = static_cast<size_t>(ceil(larger.size() / 2.0));

        BigInt num1_high, num1_low;
        num1_high = larger.substr(0, half_length);
        num1_low = larger.substr(half_length);

        BigInt num2_high, num2_low;
        num2_high = smaller.substr(0, half_length);
        num2_low = smaller.substr(half_length);

        StripLeadingZeros(num1_high.value);
        StripLeadingZeros(num1_low.value);
        StripLeadingZeros(num2_high.value);
        StripLeadingZeros(num2_low.value);

        BigInt prod_high, prod_mid, prod_low;
        prod_high = num1_high * num2_high;
        prod_low = num1_low * num2_low;
        prod_mid = (num1_high + num1_low) * (num2_high + num2_low)
            - prod_high - prod_low;

        AddTrailingZeroes(prod_high.value, 2 * half_length_ceil);
        AddTrailingZeroes(prod_mid.value, half_length_ceil);

        StripLeadingZeros(prod_high.value);
        StripLeadingZeros(prod_mid.value);
        StripLeadingZeros(prod_low.value);

        product = prod_high + prod_mid + prod_low;
    }
    StripLeadingZeros(product.value);

    if (left.sign == right.sign)
        product.sign = '+';
    else
        product.sign = '-';

    return product;
}

std::tuple<BigInt, BigInt> divide(const BigInt& dividend, const BigInt& divisor)
{
    BigInt temp = divisor;
    BigInt quotient = 1;
    BigInt remainder;
    while (temp < dividend)
    {
        ++quotient;
        temp += divisor;
    }
    if (temp > dividend)
    {
        --quotient;
        remainder = dividend - (temp - divisor);
    }

    return std::make_tuple(quotient, remainder);
}

BigInt operator/(const BigInt& left, const BigInt& right)
{
    BigInt absDividend = abs(left);
    BigInt absDivisor = abs(right);

    if (right == BigInt::Zero)
        throw std::logic_error("Attempted division by zero");
    if (absDividend < absDivisor)
        return BigInt::Zero;
    if (right == 1)
        return left;
    if (right == -1)
        return -(left);

    BigInt quotient;
    if (absDividend <= LLONG_MAX && absDivisor <= LLONG_MAX)
    {
        quotient = std::stoll(absDividend.value) / std::stoll(absDivisor.value);
    }
    else if (absDividend == absDivisor)
    {
        quotient = 1;
    }
    else if (IsPowerOf10(absDivisor.value))
    { // if divisor is a power of 10 do optimised calculation
        size_t digits_in_quotient = absDividend.value.size() - absDivisor.value.size() + 1;
        quotient.value = absDividend.value.substr(0, digits_in_quotient);
    }
    else
    {
        quotient.value = "";    // the value is cleared as digits will be appended
        BigInt chunk, chunk_quotient, chunk_remainder;
        size_t chunk_index = 0;
        chunk_remainder.value = absDividend.value.substr(chunk_index, absDivisor.value.size() - 1);
        chunk_index = absDivisor.value.size() - 1;
        while (chunk_index < absDividend.value.size())
        {
            chunk.value = chunk_remainder.value.append(1, absDividend.value[chunk_index]);
            chunk_index++;
            while (chunk < absDivisor)
            {
                quotient.value += "0";
                if (chunk_index < absDividend.value.size())
                {
                    chunk.value.append(1, absDividend.value[chunk_index]);
                    chunk_index++;
                }
                else
                    break;
            }
            if (chunk == absDivisor)
            {
                quotient.value += "1";
                chunk_remainder = 0;
            }
            else if (chunk > absDivisor)
            {
                StripLeadingZeros(chunk.value);
                std::tie(chunk_quotient, chunk_remainder) = divide(chunk, absDivisor);
                quotient.value += chunk_quotient.value;
            }
        }
    }
    StripLeadingZeros(quotient.value);

    if (left.sign == right.sign)
        quotient.sign = '+';
    else
        quotient.sign = '-';

    return quotient;
}

BigInt operator%(const BigInt& left, const BigInt& right)
{
    BigInt absDividend = abs(left);
    BigInt absDivisor = abs(right);

    if (absDivisor == BigInt::Zero)
        throw std::logic_error("Attempted division by zero");
    if (absDivisor == 1 || absDivisor == absDividend)
        return BigInt::Zero;

    BigInt remainder;
    if (absDividend <= LLONG_MAX && absDivisor <= LLONG_MAX)
    {
        remainder = std::stoll(absDividend.value) % std::stoll(absDivisor.value);
    }
    else if (absDividend < absDivisor)
    {
        remainder = absDividend;
    }
    else if (IsPowerOf10(right.value))
    { // if num is a power of 10 use optimised calculation
        size_t no_of_zeroes = right.value.size() - 1;
        remainder.value = absDividend.value.substr(absDividend.value.size() - no_of_zeroes);
    }
    else
    {
        BigInt quotient = absDividend / absDivisor;
        remainder = absDividend - quotient * absDivisor;
    }
    StripLeadingZeros(remainder.value);

    // remainder has the same sign as that of the dividend
    remainder.sign = left.sign;
    if (remainder.value == "0")     // except if its zero
        remainder.sign = '+';

    return remainder;
}

BigInt& BigInt::operator+=(const BigInt& num)
{
    *this = *this + num;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& num)
{
    *this = *this - num;
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& num)
{
    *this = *this * num;
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& num)
{
    *this = *this / num;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& num)
{
    *this = *this % num;
    return *this;
}

BigInt& BigInt::operator++()
{
    *this += 1;
    return *this;
}

BigInt& BigInt::operator--()
{
    *this -= 1;
    return *this;
}

BigInt BigInt::operator++(int)
{
    BigInt temp = *this;
    *this += 1;
    return temp;
}

BigInt BigInt::operator--(int)
{
    BigInt temp = *this;
    *this -= 1;
    return temp;
}

bool operator<(const BigInt& left, const BigInt& right)
{
    if (left.sign == right.sign)
    {
        if (left.sign == '+')
        {
            if (left.value.length() == right.value.length())
                return left.value < right.value;
            else
                return left.value.length() < right.value.length();
        }
        else
            return -left > -right;
    }
    else
        return left.sign == '-';
}

bool operator>(const BigInt& left, const BigInt& right)
{
    return !((left < right) || (left == right));
}

bool operator<=(const BigInt& left, const BigInt& right)
{
    return (left < right) || (left == right);
}

bool operator>=(const BigInt& left, const BigInt& right)
{
    return !(left < right);
}

bool operator==(const BigInt& left, const BigInt& right)
{
    return (left.sign == right.sign) && (left.value == right.value);
}

bool operator!=(const BigInt& left, const BigInt& right)
{
    return  !(left == right);
}

std::istream& operator>>(std::istream& in, BigInt& num)
{
    std::string input;
    in >> input;
    num = BigInt(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num)
{
    if (num.sign == '-')
        out << num.sign;
    out << num.value;
    return out;
}

int64_t BigInt::ToInt64() const
{
    return std::stoll(this->ToString());
}

BigInt BigInt::Pow(const BigInt& base, BigInt& exp)
{
    if (exp < 0)
    {
        if (base == Zero)
            throw std::logic_error("Cannot divide by zero");
        return abs(base) == 1 ? base : 0;
    }
    if (exp == 0)
    {
        if (base == Zero)
            throw std::logic_error("Zero cannot be raised to zero");
        return 1;
    }

    BigInt result = base, result_odd = 1;
    while (exp > 1)
    {
        if (exp % 2 != 0)
            result_odd *= result;
        result *= result;
        exp /= BigInt(2);
    }

    return result * result_odd;
}

BigInt BigInt::InverseOfModuloN(const BigInt& a, const BigInt& n)
{
    BigInt d, x, y;
    ExtendedEuclid(a, n, &x, &y, &d);
    if (d == 1)
        return x;
    return 0;
}

void BigInt::ExtendedEuclid(BigInt a, BigInt b, BigInt* x, BigInt* y, BigInt* d)
{
    BigInt q, r, x1, x2, y1, y2;
    if (b == 0)
    {
        *d = a; *x = 1; *y = 0;
        return;
    }
    x2 = y1 = 1; x1 = y2 = 0;
    while (b > 0)
    {
        q = a / b;
        r = a - q * b;
        *x = x2 - q * x1;
        *y = y2 - q * y1;
        a = b, b = r;
        x2 = x1;
        x1 = *x;
        y2 = y1;
        y1 = *y;
    }
    *d = a; *x = x2; *y = y2;
}

bool BigInt::IsPrime() const
{
    if (*this <= 1)
        return false;
    for (BigInt i = 2; i < *this; i++)
    {
        if (*this % i == 0)
            return false;
    }
    return true;
}