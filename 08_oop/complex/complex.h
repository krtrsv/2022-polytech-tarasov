#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
  int r_part;
  int i_part;

public:
  Complex(int r, int i) : r_part(r), i_part(i){};
  Complex operator+(const Complex rv) const;
  Complex operator-(const Complex rv) const;
  bool operator==(const Complex rv) const;
  double abs() const;
};

#endif
