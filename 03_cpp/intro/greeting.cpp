#include <iostream>

int main() {
  std::cout << "Enter your name, please: ";
  std::string username;
  std::cin >> username;
  std::cout << "\nHello, " << username << "!" << std::endl;
  return 0;
}
