#include <cassert>
#include <iostream>

int gcd(int a, int b) {

  if (a < 0)
    a *= -1;
  if (b < 0)
    b *= -1;

  // Решение тут
  int max, min;
  if (a < b) {
    max = b;
    min = a;
  } else if (a > b) {
    max = a;
    min = b;
  } else {
    return a;
  }

  if (a == 0 || b == 0) {
    return max;
  }
  return gcd(min, max - min);
}

int main() {
  assert(gcd(0, 5) == 5);
  assert(gcd(9, 0) == 9);
  assert(gcd(48, 64) == 16);
  assert(gcd(-64, 48) == 16);
  assert(gcd(30, 18) == 6);
  assert(gcd(-30, -18) == 6);
  assert(gcd(270, 192) == 6);

  return 0;
}
