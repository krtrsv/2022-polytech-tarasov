#include "token.hpp"
#include <deque>
#include <iostream>
#include <regex>

// Returns pair of tokens and unknown characters
std::deque<Token> tokenize(std::string expr) {
  if (expr.empty()) {
    return std::deque<Token>{Token{0}};
  }
  std::deque<Token> tokens;
  std::regex r(R"(\d+|[+\-*/^()])");

  // Splitting expression to tokens
  auto tokens_begin = std::sregex_iterator(expr.begin(), expr.end(), r);
  auto tokens_end = std::sregex_iterator();

  if (std::distance(tokens_begin, tokens_end) == 0) {
    return std::deque<Token>{Token{0}};
  }

  // Default token type
  auto type = Token::Type::Operator;

  for (std::sregex_iterator i = tokens_begin; i != tokens_end; ++i) {
    std::string t = i->str();
    if (t == "+" || t == "-") {
      if (((!tokens.empty() &&
            (tokens.back().type == Token::Type::Operator ||
             tokens.back().type == Token::Type::LeftParenthesis ||
             tokens.back().type == Token::Type::RightParenthesis)) ||
           tokens.empty()) &&
          i != tokens_end)
        tokens.push_back(Token{std::stoi(t + (++i)->str())});
      else
        tokens.push_back(Token{type, t, 1, false});
    } else if (t == "*" || t == "/")
      tokens.push_back(Token{type, t, 2, false});
    else if (t == "^")
      tokens.push_back(Token{type, t, 3, true});
    else if (t == "(")
      tokens.push_back(Token{Token::Type::LeftParenthesis, t, -1, false});
    else if (t == ")")
      tokens.push_back(Token{Token::Type::RightParenthesis, t, -1, false});
    else if (std::find_if(t.begin(), t.end(),
                          [](auto c) { return !std::isdigit(c); }) == t.end())
      tokens.push_back(Token(std::stoi(t)));
  }
  return tokens;
}
