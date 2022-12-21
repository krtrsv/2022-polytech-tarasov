#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "./hash.hpp"

#include <doctest.h>

TEST_CASE("whatever") {
  CHECK_EQ(cool_hash("test"), 2808886271);
  CHECK_EQ(cool_hash("tset"), 2757299091);
  CHECK_EQ(cool_hash("tste"), 4027122173);
}
