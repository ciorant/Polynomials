# Z3 Polynomial Library

## Overview

Z3 Polynomial Library is a robust C++ implementation that facilitates arithmetic operations on polynomials with coefficients in the field Z₃ (integers modulo 3). This library demonstrates advanced object-oriented programming principles while providing a mathematically sound implementation of polynomial operations.

## Features

- **Z₃ Field Operations**: Full arithmetic operations in the Z₃ field (addition, subtraction, multiplication, division)
- **Polynomial Arithmetic**: Complete polynomial operations including:
  - Addition and subtraction
  - Multiplication (polynomial by polynomial, scalar by polynomial)
  - Division by scalar
  - Polynomial division with remainder
- **Object-Oriented Design**: Implementation follows best practices in OOP:
  - Encapsulation through private member variables with public getters/setters
  - Clean inheritance hierarchy
  - Operator overloading for intuitive syntax
  - Copy constructors and assignment operators
- **Memory Management**: Implements proper memory allocation and deallocation
- **Input/Output Handling**: Stream operators for easy I/O operations

## Mathematical Background

This library implements polynomial operations over the field Z₃, which consists of the integers {0, 1, 2} with arithmetic performed modulo 3.

Some interesting properties of Z₃:
- Addition: `(a + b) % 3`
- Multiplication: `(a * b) % 3`
- Subtraction: `(a - b) % 3`, properly handling negative results
- Division: In Z₃, division by a non-zero element is equivalent to multiplication by its inverse


## Usage Examples

### Creating and Operating on Z₃ Elements

```cpp
#include "Z3.h"
#include <iostream>

int main() {
    Z3 a(1);  // Creates 1 in Z₃
    Z3 b(5);  // Creates 2 in Z₃ (5 % 3 = 2)
    
    Z3 sum = a + b;      // 1 + 2 = 0 (mod 3)
    Z3 product = a * b;  // 1 * 2 = 2 (mod 3)
    
    std::cout << "Sum: " << sum.getValue() << std::endl;       // Output: 0
    std::cout << "Product: " << product.getValue() << std::endl; // Output: 2
    
    return 0;
}
```

### Working with Z₃ Polynomials

```cpp
#include "Polynomial.h"
#include <iostream>

int main() {
    // Create polynomial p(x) = 1 + 2x + x²
    Z3 coeffs1[3] = {Z3(1), Z3(2), Z3(1)};
    Polynomial p(2, coeffs1);
    
    // Create polynomial q(x) = 2 + x
    Z3 coeffs2[2] = {Z3(2), Z3(1)};
    Polynomial q(1, coeffs2);
    
    // Operations
    Polynomial sum = p + q;   // (1 + 2x + x²) + (2 + x) = 0 + 0x + x²
    Polynomial prod = p * q;  // (1 + 2x + x²) * (2 + x) = 2 + 2x + 0x² + x³
    
    std::cout << "p(x) = " << p.toString() << std::endl;
    std::cout << "q(x) = " << q.toString() << std::endl;
    std::cout << "Sum: " << sum.toString() << std::endl;
    std::cout << "Product: " << prod.toString() << std::endl;
    
    // Polynomial division
    Polynomial quotient, remainder;
    polynomialDivision(prod, p, quotient, remainder);
    
    std::cout << "Dividing " << prod.toString() << " by " << p.toString() << ":" << std::endl;
    std::cout << "Quotient: " << quotient.toString() << std::endl;
    std::cout << "Remainder: " << remainder.toString() << std::endl;
    
    return 0;
}
```


Code Design Principles

This project demonstrates several important software design principles:

1. **Encapsulation**: Member variables are private with controlled access
2. **Immutability**: Operations return new objects rather than modifying existing ones
3. **Exception Safety**: Proper error handling for operations like division by zero
4. **Memory Management**: Careful allocation and deallocation to prevent memory leaks
5. **Operator Overloading**: Natural mathematical syntax through C++ operator overloading

---

<div align="center">
  <sub>Built with ❤️ for modern C++ and mathematical elegance</sub>
</div>
