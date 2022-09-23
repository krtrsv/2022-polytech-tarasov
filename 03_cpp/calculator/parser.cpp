#include "parser.hpp"
#include <algorithm>
#include <deque>
#include <math.h>
#include <vector>

// std::deque<Token> shunting_yard(std::deque<Token> tokens) {
//
//   // https://en.wikipedia.org/wiki/Shunting_yard_algorithm
//   std::deque<Token> output_queue;
//   std::vector<Token> operator_stack;
//
//   // while there are tokens to be read:
//   for (Token tok : tokens) {
//
//     // if the token is:
//     switch (tok.type) {
//
//     // a number:
//     case Token::Type::Number:
//
//       // put it into the output queue
//       output_queue.push_back(tok);
//       break;
//
//     // an operator o1:
//     case Token::Type::Operator: {
//       auto o1 = tok;
//
//       // while (
//       // there is an operator o2 other than the left parenthesis at the top
//       // of the operator stack, and (o2 has greater precedence than o1,
//       // or they have the same precedence and o1 is left-associative)
//       // ):
//       while (!operator_stack.empty()) {
//         auto o2 = operator_stack.back();
//         if ((!o1.right_associative && o1.precedence <= o2.precedence) ||
//             (o1.right_associative && o1.precedence < o2.precedence)) {
//
//           // pop o2 from the operator stack into the output queue
//           operator_stack.pop_back();
//           output_queue.push_back(o2);
//           continue;
//         }
//         break;
//       }
//
//       // push o1 onto the operator stack
//       operator_stack.push_back(o1);
//     } break;
//
//     // a left parenthesis (i.e. "("):
//     case Token::Type::LeftParenthesis:
//
//       // push it onto the operator stack
//       operator_stack.push_back(tok);
//       break;
//
//     // a right parenthesis (i.e. ")"):
//     case Token::Type::RightParenthesis:
//       // If token is right parenthesis:
//       {
//         bool match = false;
//
//         // Until the token at the top of the stack
//         // is a left parenthesis,
//         while (!operator_stack.empty() &&
//                operator_stack.back().type != Token::Type::LeftParenthesis) {
//           // pop operators off the stack
//           // onto the output queue.
//           output_queue.push_back(operator_stack.back());
//           operator_stack.pop_back();
//           match = true;
//         }
//
//         // Pop the left parenthesis from the stack,
//         // but not onto the output queue.
//         operator_stack.pop_back();
//
//         if (!match && operator_stack.empty()) {
//           // If the stack runs out without finding a left parenthesis,
//           // then there are mismatched parentheses.
//           return {};
//         }
//       }
//       break;
//
//     default:
//       break;
//     }
//   }
//
//   // while there are tokens on the operator stack:
//   while (!operator_stack.empty()) {
//
//     // {assert the operator on top of the stack is not a (left) parenthesis}
//     if (operator_stack.back().type != Token::Type::LeftParenthesis) {
//
//       // pop the operator from the operator stack onto the output queue
//       output_queue.push_back(std::move(operator_stack.back()));
//       operator_stack.pop_back();
//     }
//   }
//
//   return output_queue;
// }

std::deque<Token> shunting_yard(std::deque<Token> tokens) {
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
      while (!stack.empty() && stack.back().type != Token::Type::LeftParenthesis) {
        queue.push_back(stack.back());
        stack.pop_back();
        match = true;
      }
      stack.pop_back();
      if (!match && stack.empty()) { return {}; }
    } break;
    default: break;
    }
  }
  while (!stack.empty()) {
    if (stack.back().type != Token::Type::LeftParenthesis) {
      queue.push_back(std::move(stack.back()));
      stack.pop_back();
    }
  }
  return queue;
}
