#include "parser.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <math.h>
#include <vector>

std::pair<int, std::deque<Token>> shunting_yard(std::deque<Token> tokens) {
  std::deque<Token> queue;
  std::vector<Token> stack;
  for (Token token : tokens) {
    switch (token.type) {
    case Token::Type::Number:
      queue.push_back(token);
      break;
    case Token::Type::Operator: {
      auto o1 = token;
      while (!stack.empty()) {
        auto o2 = stack.back();
        if ((!o1.right_associative && o1.precedence <= o2.precedence) ||
            (o1.right_associative && o1.precedence < o2.precedence)) {
          stack.pop_back();
          queue.push_back(o2);
          continue;
        }
        break;
      }
      stack.push_back(o1);
    } break;
    case Token::Type::LeftParenthesis:
      stack.push_back(token);
      break;
    case Token::Type::RightParenthesis: {
      bool match = false;
      while (!stack.empty() &&
             stack.back().type != Token::Type::LeftParenthesis) {
        queue.push_back(stack.back());
        stack.pop_back();
      }
      if (stack.empty()) {
        return std::pair<int, std::deque<Token>>(-1, {});
      }
      stack.pop_back();
    } break;
    default:
      break;
    }
  }
  while (!stack.empty()) {
    if (stack.back().type == Token::Type::LeftParenthesis)
      return std::pair<int, std::deque<Token>>(-1, {});
    queue.push_back(std::move(stack.back()));
    stack.pop_back();
  }
  return std::pair<int, std::deque<Token>>(0, queue);
}
