#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
  enum class Type { Number, Operator, LeftParenthesis, RightParenthesis };

  Type type;

  std::string str;
  int num;
  bool right_associative;
  int precedence;

  Token(Type t, std::string s, int p = -1, bool a = false); // For operators
  Token(int n);                                             // For numbers
};

#endif
