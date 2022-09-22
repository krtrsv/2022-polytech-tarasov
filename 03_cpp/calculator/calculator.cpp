#include <deque>
#include <iostream>
#include "parser.h"
#include "colors.h"

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
  std::cout << "\n    " << ITALIC << BOLD;
  for (Token token : tokens) {
      if (token.type == Token::Type::Number) {
        std::cout << CYAN;
        std::cout << token.num << " ";
      } else {
        std::cout << WHITE;
        std::cout << token.str << " ";
      }
  }
  std::cout << WHITE << "= " << GREEN << res << RESET << "\n" << std::endl;

  // Infinite recursion
  return main();
}
