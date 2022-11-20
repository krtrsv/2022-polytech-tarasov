#include <cassert>

unsigned int length(const char *str) {
  if (!str)
    return 0;
  const char *end = str;
  for (; *end != '\0'; ++end)
    ;
  return end - str;
}

bool ispalindrome(const char *str) {
  if (!str || !str[0])
    return false;
  int len = length(str);
  for (int i = 0; i < len / 2; ++i) {
    if (str[i] != str[len - 1 - i])
      return false;
  }
  return true;
}

int main() {
  assert(ispalindrome("tenet") == true);
  assert(ispalindrome("") == false);
  assert(ispalindrome("hello world") == false);
  assert(ispalindrome(nullptr) == false);
  return 0;
}
