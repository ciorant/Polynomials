
#include "Polynomial.h"
#include <cstring>
#include <stdexcept>

Polynomial::Polynomial() {
    m_degree = 0;
    m_coefficients = new Z3[1];
    m_coefficients[0].setValue(0);
}

Polynomial::Polynomial(unsigned int degree, Z3* coefficients) {
    if (coefficients == nullptr || (coefficients[0].getValue() == 0 && degree == 0)) {
        m_degree = 0;
        m_coefficients = new Z3[1];
        m_coefficients[0].setValue(0);
        return;
    }

    unsigned int actualDegree = degree;
    while (actualDegree > 0 && coefficients[actualDegree].getValue() == 0) {
        --actualDegree;
    }

    m_degree = actualDegree;
    m_coefficients = new Z3[m_degree + 1];

    for (unsigned int i = 0; i <= m_degree; ++i) {
        m_coefficients[i] = coefficients[i];
    }
}

Polynomial::Polynomial(const Polynomial& other) : m_degree(other.m_degree) {
    m_coefficients = new Z3[m_degree + 1];
    for (unsigned int i = 0; i <= m_degree; ++i) {
        m_coefficients[i] = other.m_coefficients[i];
    }
}

Polynomial::~Polynomial() {
    delete[] m_coefficients;
}

Z3 Polynomial::getCoefficient(unsigned int power) const {
    if (power > m_degree) {
        return Z3(0);
    }
    return m_coefficients[power];
}

void Polynomial::setCoefficient(unsigned int power, const Z3& value) {
    if (power > m_degree) {
        if (value.getValue() == 0) {
            return;
        }

        Z3* newCoefficients = new Z3[power + 1];

        for (unsigned int i = 0; i <= m_degree; ++i) {
            newCoefficients[i] = m_coefficients[i];
        }

        for (unsigned int i = m_degree + 1; i < power; ++i) {
            newCoefficients[i].setValue(0);
        }

        newCoefficients[power] = value;

        delete[] m_coefficients;
        m_coefficients = newCoefficients;
        m_degree = power;
    } else {
        m_coefficients[power] = value;

        if (power == m_degree && value.getValue() == 0) {
            normalize();
        }
    }
}

unsigned int Polynomial::getDegree() const {
    int i = static_cast<int>(m_degree);
    while (i >= 0 && m_coefficients[i].getValue() == 0) {
        i--;
    }
    return (i < 0) ? 0 : i;
}

Polynomial& Polynomial::normalize() {
    int i = static_cast<int>(m_degree);

    while (i >= 0 && m_coefficients[i].getValue() == 0) {
        --i;
    }

    if (i < 0) {
        delete[] m_coefficients;
        m_degree = 0;
        m_coefficients = new Z3[1];
        m_coefficients[0].setValue(0);
        return *this;
    }

    if (static_cast<unsigned int>(i) != m_degree) {
        Z3* newCoefficients = new Z3[i + 1];
        for (int j = 0; j <= i; ++j) {
            newCoefficients[j] = m_coefficients[j];
        }
        delete[] m_coefficients;
        m_coefficients = newCoefficients;
        m_degree = i;
    }

    return *this;
}

std::string Polynomial::toString(const std::string& variableName) const {
    Polynomial temp(*this);
    temp.normalize();

    if (temp.m_degree == 0 && temp.m_coefficients[0].getValue() == 0) {
        return "0";
    }

    if (temp.m_degree == 0) {
        return std::to_string(temp.m_coefficients[0].getValue());
    }

    std::string result;

    if (temp.m_coefficients[0].getValue() != 0) {
        result = std::to_string(temp.m_coefficients[0].getValue()) + "+";
    }

    for (unsigned int i = 1; i < temp.m_degree; ++i) {
        if (temp.m_coefficients[i].getValue() == 0) {
            continue;
        }

        std::string coef_str = std::to_string(temp.m_coefficients[i].getValue());
        std::string exp_str = std::to_string(i);
        result += coef_str + "*" + variableName + "^" + exp_str + "+";
    }

    std::string coef_str = std::to_string(temp.m_coefficients[temp.m_degree].getValue());
    std::string exp_str = std::to_string(temp.m_degree);
    result += coef_str + "*" + variableName + "^" + exp_str;

    return result;
}

Z3 Polynomial::operator[](unsigned int power) const {
    return getCoefficient(power);
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    *this = *this + other;
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    *this = *this - other;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    *this = (*this) * other;
    return *this;
}

Polynomial& Polynomial::operator*=(const Z3& scalar) {
    *this = scalar * (*this);
    return *this;
}

Polynomial& Polynomial::operator/=(const Z3& scalar) {
    *this = (*this) / scalar;
    return *this;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) {
        return *this;
    }

    delete[] m_coefficients;
    m_degree = other.m_degree;
    m_coefficients = new Z3[m_degree + 1];

    memcpy(m_coefficients, other.m_coefficients, sizeof(Z3) * (m_degree + 1));
    return *this;
}

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
    unsigned int maxDegree = (a.getDegree() > b.getDegree()) ? a.getDegree() : b.getDegree();
    Z3* resultCoefficients = new Z3[maxDegree + 1];

    for (unsigned int i = 0; i <= maxDegree; ++i) {
        resultCoefficients[i] = a.getCoefficient(i) + b.getCoefficient(i);
    }

    Polynomial result(maxDegree, resultCoefficients);
    delete[] resultCoefficients;
    return result.normalize();
}

Polynomial operator-(const Polynomial& a) {
    Z3* resultCoefficients = new Z3[a.getDegree() + 1];

    for (unsigned int i = 0; i <= a.getDegree(); ++i) {
        Z3 coef = a.getCoefficient(i);
        if (coef.getValue() == 0) {
            resultCoefficients[i].setValue(0);
        } else if (coef.getValue() == 1) {
            resultCoefficients[i].setValue(2);
        } else if (coef.getValue() == 2) {
            resultCoefficients[i].setValue(1);
        }
    }

    Polynomial result(a.getDegree(), resultCoefficients);
    delete[] resultCoefficients;
    return result;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b) {
    return a + (-b);
}

Polynomial operator*(const Polynomial& a, const Polynomial& b) {
    unsigned int resultDegree = a.getDegree() + b.getDegree();
    Z3* resultCoefficients = new Z3[resultDegree + 1];

    for (unsigned int i = 0; i <= resultDegree; ++i) {
        resultCoefficients[i].setValue(0);
    }

    for (unsigned int i = 0; i <= b.getDegree(); ++i) {
        for (unsigned int j = 0; j <= a.getDegree(); ++j) {
            resultCoefficients[i + j] += b.getCoefficient(i) * a.getCoefficient(j);
        }
    }

    Polynomial result(resultDegree, resultCoefficients);
    delete[] resultCoefficients;
    return result.normalize();
}

Polynomial operator*(const Z3& scalar, const Polynomial& a) {
    Z3* resultCoefficients = new Z3[a.getDegree() + 1];

    for (unsigned int i = 0; i <= a.getDegree(); ++i) {
        resultCoefficients[i] = a.getCoefficient(i) * scalar;
    }

    Polynomial result(a.getDegree(), resultCoefficients);
    delete[] resultCoefficients;
    return result.normalize();
}

Polynomial operator/(const Polynomial& a, const Z3& scalar) {
    if (scalar.getValue() == 0) {
        throw std::invalid_argument("Division by zero");
    }

    return scalar * a;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
    out << '{' << p.getCoefficient(0);

    for (unsigned int i = 1; i <= p.getDegree(); ++i) {
        out << ',' << p.getCoefficient(i);
    }

    out << '}';
    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& p) {
    char c;

    while ((c = in.get()) != '{');

    Z3 coefficients[2501] = {}; // For simplicity, may well use std::vector here
    int i = 0;
    short int temp;

    while (true) {
        in >> temp;
        coefficients[i].setValue(temp);
        ++i;
        in.get(c);
        if (c == '}') break;
    }

    Polynomial tempPoly(2500, coefficients);
    p = tempPoly.normalize();
    return in;
}

void polynomialDivision(const Polynomial& dividend, const Polynomial& divisor,
                      Polynomial& quotient, Polynomial& remainder) {
    Polynomial u = dividend;
    Polynomial v = divisor;

    u.normalize();
    v.normalize();

    if (v.getDegree() == 0 && v.getCoefficient(0).getValue() == 0) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    quotient = Polynomial();
    remainder = u;

    unsigned int divisorDegree = v.getDegree();
    Z3 leadingCoefficient = v.getCoefficient(divisorDegree);

    while (remainder.getDegree() >= divisorDegree) {
        unsigned int termDegree = remainder.getDegree() - divisorDegree;
        Z3* termCoefficients = new Z3[termDegree + 1];

        for (unsigned int i = 0; i <= termDegree; ++i) {
            termCoefficients[i].setValue(0);
        }

        termCoefficients[termDegree] = remainder.getCoefficient(remainder.getDegree()) / leadingCoefficient;

        Polynomial term(termDegree, termCoefficients);
        delete[] termCoefficients;

        quotient = quotient + term;
        remainder = remainder - (term * v);
        remainder.normalize();

        if (remainder.getDegree() == 0 && remainder.getCoefficient(0).getValue() == 0) {
            break;
        }
    }

    quotient.normalize();
}