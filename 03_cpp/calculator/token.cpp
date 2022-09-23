#include "token.hpp"

Token::Token(Type t, std::string s, int p, bool a)
    : type{t}, str{s}, right_associative{a}, precedence{p} {}
Token::Token(int n) : type{Token::Type::Number}, num{n} {}
