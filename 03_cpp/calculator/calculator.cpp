#include <iostream>
#include <algorithm>
#include <math.h>

int main() {
  // Initialize expression string
  std::string expr;

  // Print prompt
  std::cout << " > ";

  // Get expression line
  std::getline(std::cin, expr);

  // Remove spaces from expression
  expr.erase(std::remove_if(expr.begin(), expr.end(), isspace), expr.end());

  std::size_t pos{};

  // Get first operand
  const int n1 {std::stoi(expr, &pos)};

  // Get operator
  const char op = expr.at(pos);

  // Get second operand
  const int n2 {std::stoi(expr.substr(++pos))};

  int res;

  // Solve expression
  switch (op) {
    case '+': res = n1 + n2; break;
    case '-': res = n1 - n2; break;
    case '*': res = n1 * n2; break;
    case '/': res = n1 / n2; break;
    case '^': res = pow(n1, n2); break;
    default:
      std::cerr << "дурак" << std::endl;
      exit(1);
  }

  std::cout << res << std::endl;

  // Infinite recursion
  return main();
}
