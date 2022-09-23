#ifndef LEXER_H
#define LEXER_H

#include "token.hpp"
#include <deque>
#include <string>

std::deque<Token> tokenize(std::string expr);

#endif
