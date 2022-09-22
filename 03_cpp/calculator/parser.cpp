#include <algorithm>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <math.h>
#include <vector>
#include "parser.h"

Token::Token(Type t, std::string s, int p, bool a) : type{t}, str{s}, right_associative{a}, precedence{p} {}
Token::Token(int n) : type{Token::Type::Number}, num{n} {}

std::deque<Token> tokenize(std::string expr) {
  std::deque<Token> tokens;

  // Remove spaces from string
  expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

  // Iterate through expression
  for (int i = 0; i < expr.length(); ++i) {

    // Add number to tokens queue
    if (isdigit(expr[i])) {
      const auto b = i;
      while(isdigit(expr[i])) {
          ++i;
      }
      const auto n = std::stoi(expr.substr(b, i));
      tokens.push_back(Token{n});
      --i;
    }

    // Add operator to tokens queue
    else {
      int pr;          // precedence
      bool ra = false; // right associativity

      switch (expr[i]) {
      case '+':
        pr = 1;
        break;
      case '-':
        pr = 1;
        break;
      case '*':
        pr = 2;
        break;
      case '/':
        pr = 2;
        break;
      case '^':
        pr = 3;
        ra = true;
        break;
      default:
        break;
      }

      tokens.push_back(
          Token{Token::Type::Operator, std::string{expr[i]}, pr, ra});
    }
  }
  return tokens;
}

std::deque<Token> shunting_yard(std::deque<Token> tokens) {

  // https://en.wikipedia.org/wiki/Shunting_yard_algorithm
  std::deque<Token> output_queue;
  std::vector<Token> operator_stack;

  // while there are tokens to be read:
  for (Token tok : tokens) {

    // if the token is:
    switch (tok.type) {

    // a number:
    case Token::Type::Number:

      // put it into the output queue
      output_queue.push_back(tok);
      break;

    // an operator o1:
    case Token::Type::Operator: {
      auto o1 = tok;

      // while (
      // there is an operator o2 other than the left parenthesis at the top
      // of the operator stack, and (o2 has greater precedence than o1,
      // or they have the same precedence and o1 is left-associative)
      // ):
      while (!operator_stack.empty()) {
        auto o2 = operator_stack.back();
        if ((!o1.right_associative && o1.precedence <= o2.precedence) ||
            (o1.right_associative && o1.precedence < o2.precedence)) {

          // pop o2 from the operator stack into the output queue
          operator_stack.pop_back();
          output_queue.push_back(o2);
          continue;
        }
        break;
      }

      // push o1 onto the operator stack
      operator_stack.push_back(o1);
    } break;

    // a left parenthesis (i.e. "("):
    case Token::Type::LeftParenthesis:

      // push it onto the operator stack
      output_queue.push_back(tok);
      break;

    // a right parenthesis (i.e. ")"):
    case Token::Type::RightParenthesis:

      // while the operator at the top of the operator stack is not a left
      // parenthesis:
      while (operator_stack.back().type != Token::Type::LeftParenthesis) {

        // {assert the operator stack is not empty}
        if (!operator_stack.empty()) {
          Token o2 = operator_stack.back();

          // pop the operator from the operator stack into the output queue
          operator_stack.pop_back();
          output_queue.push_back(o2);
        }
      }

      // {assert there is a left parenthesis at the top of the operator stack}
      if (operator_stack.back().type == Token::Type::LeftParenthesis) {

        // pop the left parenthesis from the operator stack and discard it
        output_queue.push_back(tok);
      }
      break;
    }
  }

  // while there are tokens on the operator stack:
  while (!operator_stack.empty()) {

    // {assert the operator on top of the stack is not a (left) parenthesis}
    if (operator_stack.back().type != Token::Type::LeftParenthesis) {

      // pop the operator from the operator stack onto the output queue
      output_queue.push_back(std::move(operator_stack.back()));
      operator_stack.pop_back();
    }
  }

  return output_queue;
}

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
