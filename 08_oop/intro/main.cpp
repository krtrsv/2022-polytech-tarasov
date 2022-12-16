#include "String.h"
#include <iostream>

int main() {
  String str1 = "Monad is a ";
  String str2 = str1 + "monoid in the category of endofunctors.";
  std::cout << "String: " << str2 << '\n'
            << "Length: " << str2.get_length() << std::endl;
  return 0;
}
