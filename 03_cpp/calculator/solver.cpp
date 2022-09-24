#include "token.hpp"
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>

std::pair<int, int> solve(std::deque<Token> queue) {
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
          return std::pair<int, int>(136, 0); // SIGFPE
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
  return std::pair<int, int>(0, stack.back());
}
