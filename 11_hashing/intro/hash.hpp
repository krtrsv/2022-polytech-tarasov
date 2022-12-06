#ifndef HASH_HPP
#define HASH_HPP

#include <algorithm>
#include <string_view>

#define A 94583
#define B 41733
#define C 19203

inline unsigned cool_hash(std::string_view s) {
  unsigned h = C;
  std::for_each(s.begin(), s.end(), [&h](char x) { h = (h * A) ^ (x * B); });
  return h;
}

#undef A
#undef B
#undef C

#endif
