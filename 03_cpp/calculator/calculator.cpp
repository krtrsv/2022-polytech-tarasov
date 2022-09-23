#include "colors.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "solver.hpp"
#include "token.hpp"
#include <deque>
#include <iostream>

int main() {
  // Initialize expression string
  std::string expr;

  // Print prompt
  std::cout << " > ";

  // Get expression line
  std::getline(std::cin, expr);

  // Normal exit
  if (expr == "exit")
    exit(0);

  // Tokenize expression
  std::deque<Token> tokens = tokenize(expr);

  // Produce postfix notation
  std::deque<Token> queue = shunting_yard(tokens);

  // Solve expression
  auto res = solve(queue);

  // Qalc-like output
  std::cout << "\n    ";
  for (Token token : tokens) {
    if (token.type == Token::Type::Number) {
      std::cout << CYAN;
      if (token.num < 0)
        std::cout << RESET << "(" << CYAN << token.num << RESET << ") ";
      else
        std::cout << CYAN << token.num << " ";

    } else {
      std::cout << RESET;
      std::cout << token.str << " ";
    }
  }
  std::cout << RESET << "= " << GREEN << res << RESET << "\n" << std::endl;

  // Infinite recursion
  return main();
}
