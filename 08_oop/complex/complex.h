#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
public:
  int r_part;
  int i_part;
  Complex(int r, int i) : r_part(r), i_part(i){};
  const Complex operator+(const Complex rv) const;
  const Complex operator-(const Complex rv) const;
  const bool operator==(const Complex rv) const;
  const double abs() const;
};

#endif
