#include "complex.h"
#include <cmath>

Complex Complex::operator+(const Complex rv) const {
  return Complex(r_part + rv.r_part, i_part + rv.i_part);
}

Complex Complex::operator-(const Complex rv) const {
  return Complex(r_part - rv.r_part, i_part - rv.i_part);
}

bool Complex::operator==(const Complex rv) const {
  return r_part == rv.r_part && i_part == rv.i_part;
}

double Complex::abs() const { return sqrt(r_part * r_part + i_part * i_part); }
