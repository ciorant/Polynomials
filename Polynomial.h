#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <string>
#include "Z3.h"

// Implements polynomials with coefficients in Z3

class Polynomial {
private:
    unsigned int m_degree;
    Z3* m_coefficients;

public:
    Polynomial();

    Polynomial(unsigned int degree, Z3* coefficients);

    Polynomial(const Polynomial& other);

    ~Polynomial();

    Z3 getCoefficient(unsigned int power) const;

    void setCoefficient(unsigned int power, const Z3& value);

    unsigned int getDegree() const;

    Polynomial& normalize(); // Remove leading zeros

    std::string toString(const std::string& variableName = "x") const;

    Z3 operator[](unsigned int power) const;
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator*=(const Z3& scalar);
    Polynomial& operator/=(const Z3& scalar);
    Polynomial& operator=(const Polynomial& other);
};

Polynomial operator+(const Polynomial& a, const Polynomial& b);
Polynomial operator-(const Polynomial& a);
Polynomial operator-(const Polynomial& a, const Polynomial& b);
Polynomial operator*(const Polynomial& a, const Polynomial& b);
Polynomial operator*(const Z3& scalar, const Polynomial& a);
Polynomial operator/(const Polynomial& a, const Z3& scalar);

std::ostream& operator<<(std::ostream& out, const Polynomial& p);
std::istream& operator>>(std::istream& in, Polynomial& p);

void polynomialDivision(const Polynomial& dividend, const Polynomial& divisor,
                        Polynomial& quotient, Polynomial& remainder);

#endif // POLYNOMIAL_H