#include <deque>
#include <cmath>
#include <vector>
#include <iostream>
#include "token.hpp"

int solve(std::deque<Token> queue) {
  std::vector<int> stack;
  while (!queue.empty()) {
    const auto token = queue.front();
    queue.pop_front();

    if (token.type == Token::Type::Number) {
      stack.push_back(token.num);
    }

    else if (token.type == Token::Type::Operator) {

      const auto rhs = stack.back();
      stack.pop_back();
      const auto lhs = stack.back();
      stack.pop_back();

      switch (token.str[0]) {
      case '^':
        stack.push_back(static_cast<int>(pow(lhs, rhs)));
        break;
      case '*':
        stack.push_back(lhs * rhs);
        break;
      case '/':
        if (rhs == 0) {
          std::cerr << "Division by zero" <<std::endl;
          return 0;
        }
        stack.push_back(lhs / rhs);
        break;
      case '+':
        stack.push_back(lhs + rhs);
        break;
      case '-':
        stack.push_back(lhs - rhs);
        break;
      default:
        break;
      }
    }
  }
  return stack.back();
}
