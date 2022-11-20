#include "complex.h"
#include <cmath>
#include <doctest.h>

const Complex Complex::operator+(const Complex rv) const {
  return Complex(r_part + rv.r_part, i_part + rv.i_part);
}
const Complex Complex::operator-(const Complex rv) const {
  return Complex(r_part - rv.r_part, i_part - rv.i_part);
}

const bool Complex::operator==(const Complex rv) const {
  return r_part == rv.r_part && i_part == rv.i_part;
}

const double Complex::abs() const {
  return sqrt(r_part * r_part + i_part * i_part);
}