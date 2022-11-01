#include <iostream>
#include <cstring>
#include "String.h"

String::String(const char *s) {
  data = (char*)malloc(strlen(s));
  strcpy(data, s);
}

unsigned int String::get_length() {
  if (!data)
    return 0;
  const char *end = data;
  for (; *end != '\0'; ++end)
    ;
  return end - data;
}

const char *String::c_str() { return data; }

String String::operator+(String rv) {
  auto dest = (char*)malloc(this->get_length());
  strcpy(dest, data);
  strcpy(dest + rv.get_length(), rv.c_str());
  return String(dest);
}

std::ostream &operator<<(std::ostream &out, String &S) {
  out << S.c_str();
  return out;
}

String::~String() = default;
