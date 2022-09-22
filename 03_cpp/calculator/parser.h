#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <deque>

class Token {

public:
  enum class Type {
    Number,
    Operator,
    LeftParenthesis,
    RightParenthesis
  };
  Type type;
  std::string str;
  int num;
  bool right_associative;
  int precedence;
  Token(Type t, std::string s, int p = 0, bool a = false);
  Token(int n);
};

std::deque<Token> tokenize(std::string expr);
std::deque<Token> shunting_yard(std::deque<Token> tokens);
int solve(std::deque<Token> queue);

#endif