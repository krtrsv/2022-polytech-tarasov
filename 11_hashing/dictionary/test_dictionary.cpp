#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "dictionary.hpp"

#include <string>
#include <doctest.h>

TEST_CASE("whatever") {

  HashTable<std::string> d1;
  d1.insert("first", "hi");
  d1.insert("secnd", "ih");

  CHECK_EQ(d1.size(), 2);
  CHECK_EQ(d1.get("first"), "hi");

}
