#ifndef Z3_H
#define Z3_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

// Arithmetic operations in Z3
class Z3 {
private:
    short int m_number;

public:

    Z3() : m_number(0) {}

    explicit Z3(short int number);

    short int getValue() const { return m_number; }

    void setValue(short int number);

    operator short int() const { return m_number; }

    Z3& operator+=(const Z3& digit);
    Z3& operator-=(const Z3& digit);
    Z3& operator*=(const Z3& digit);
    Z3& operator/=(const Z3& digit);
};

Z3 operator+(const Z3& digit1, const Z3& digit2);
Z3 operator-(const Z3& digit1, const Z3& digit2);
Z3 operator*(const Z3& digit1, const Z3& digit2);
Z3 operator/(const Z3& digit1, const Z3& digit2);

std::ostream& operator<<(std::ostream& out, const Z3& digit);

#endif // Z3_H