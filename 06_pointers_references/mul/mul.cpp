#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

unsigned int length(const char *str) {
  if (!str)
    return 0;
  const char *end = str;
  for (; *end != '\0'; ++end)
    ;
  return end - str;
}

const char *itos(int N) {
  if (!N)
    return "0";
  int m = N;
  int digit = 0;
  while (m) {
    digit++;
    m /= 10;
  }
  char *arr;
  char arr1[digit];
  arr = (char *)malloc(digit);
  int index = 0;
  while (N) {
    arr1[++index] = N % 10 + '0';
    N /= 10;
  }
  int i;
  for (i = 0; i < index; i++) {
    arr[i] = arr1[index - i];
  }
  arr[i] = '\0';
  return (const char *)arr;
}

const char *mul(const char *fst, const char *snd) {
  int fsti = 0, sndi = 0;
  for (int i = 0, mult = 1; i != length(fst); ++i, mult *= 10)
    fsti += (fst[i] - '0') * mult;
  for (int i = 0, mult = 1; i != length(snd); ++i, mult *= 10)
    sndi += (snd[i] - '0') * mult;
  return itos((fsti * sndi));
}

int main() {
  assert(strcmp(mul("5", "2"), "10") == 0);
  assert(strcmp(mul("0", "1"), "0") == 0);
  assert(strcmp(mul("99", "99"), "9801") == 0);
  return 0;
}
