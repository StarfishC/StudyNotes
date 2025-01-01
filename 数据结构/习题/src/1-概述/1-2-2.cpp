// File:    1-2-2.cpp
// Author:  csh
// Date:    2020/06/13
// Update:  2024/12/07
// ===================

#include <iostream>

class Complex
{
public:
    Complex(double r, double i) :
        re(r), im(i){};
    Complex() :
        Complex(0, 0){};
    explicit Complex(double r) :
        Complex(r, 0){};

    double Real() const { return re; }
    double Imag() const { return im; }

private:
    double re;
    double im;
};

inline Complex operator+(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.Real() + rhs.Real(), lhs.Imag() + lhs.Imag());
}
inline Complex operator-(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.Real() - rhs.Real(), lhs.Imag() - lhs.Imag());
}
inline Complex operator*(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.Real() * rhs.Real(), lhs.Imag() * lhs.Imag());
}
inline Complex operator/(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.Real() / rhs.Real(), lhs.Imag() / lhs.Imag());
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << "(" << c.Real() << "," << c.Imag() << ")";
    return os;
}
