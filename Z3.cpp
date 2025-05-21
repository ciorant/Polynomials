
#include "Z3.h"
#include <stdexcept>

Z3::Z3(short int number) {
    setValue(number);
}

void Z3::setValue(short int number) {
    number = number % 3;
    if (number < 0) {
        number += 3;
    }
    m_number = number;
}

Z3& Z3::operator+=(const Z3& digit) {
    m_number = (m_number + digit.m_number) % 3;
    return *this;
}

Z3& Z3::operator-=(const Z3& digit) {
    short int result = (m_number - digit.m_number) % 3;
    if (result < 0) {
        result += 3;
    }
    m_number = result;
    return *this;
}

Z3& Z3::operator*=(const Z3& digit) {
    m_number = (m_number * digit.m_number) % 3;
    return *this;
}

Z3& Z3::operator/=(const Z3& digit) {
    if (digit.m_number == 0) {
        throw std::invalid_argument("Division by zero in Z3");
    }

    // In Z3, division by non-zero is equivalent to multiplication by the inverse
    *this *= digit;
    return *this;
}

Z3 operator+(const Z3& digit1, const Z3& digit2) {
    Z3 result = digit1;
    result += digit2;
    return result;
}

Z3 operator-(const Z3& digit1, const Z3& digit2) {
    Z3 result = digit1;
    result -= digit2;
    return result;
}

Z3 operator*(const Z3& digit1, const Z3& digit2) {
    Z3 result = digit1;
    result *= digit2;
    return result;
}

Z3 operator/(const Z3& digit1, const Z3& digit2) {
    if (digit2.getValue() == 0) {
        throw std::invalid_argument("Division by zero in Z3");
    }
    return digit1 * digit2;
}

std::ostream& operator<<(std::ostream& out, const Z3& digit) {
    out << digit.getValue();
    return out;
}