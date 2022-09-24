#ifndef PARSER_H
#define PARSER_H

#include "token.hpp"
#include <deque>
#include <string>

std::pair<int, std::deque<Token>> shunting_yard(std::deque<Token> tokens);

#endif
