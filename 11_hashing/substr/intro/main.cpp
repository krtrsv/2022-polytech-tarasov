#include "String.h"
#include <iostream>

int main() {
  String foo = "help";
  String bar = foo + " pls";
  std::cout << bar << '\n' << bar.get_length();
  return 0;
}
