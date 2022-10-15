#include <cassert>
#include <cstring>

unsigned int length(const char* str) {
  return (str == nullptr) ? 0 : strlen(str);
}

int main() {
  assert(length("a") == 1);
  assert(length("ab") == 2);
  assert(length("") == 0);
  assert(length("hello world") == 11);
  assert(length(nullptr) == 0);
  return 0;
}
