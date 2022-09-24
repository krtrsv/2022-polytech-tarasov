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
  if (std::cin.fail() || expr == "exit") {
    std::cout << ITALIC << "\n Goodbye, desu\n" << RESET << std::endl;
    exit(0);
  }

  // Tokenize expression
  std::deque<Token> tokens = tokenize(expr);

  // Produce postfix notation
  auto queue = shunting_yard(tokens);

  // Catch mismatched parentheses
  if (queue.first == -1) {
    std::cerr << RED << "\n  Error" << RESET << ": " << ITALIC
              << "Mismatched parentheses, desu\n"
              << RESET << std::endl;
    // Start again
    return main();
  }

  // Solve expression
  auto res = solve(queue.second);

  // Catch sigfpe
  if (res.first == 136) {
    std::cerr << RED << "\n  Error" << RESET << ": " << ITALIC
              << "Division by zero, desu\n"
              << RESET << std::endl;
    // Start again
    return main();
  }

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
  std::cout << RESET << "= " << GREEN << res.second << RESET << "\n"
            << std::endl;

  // Infinite recursion
  return main();
}
