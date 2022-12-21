#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tree.hpp"

#include <doctest.h>
#include <stdexcept>

TEST_CASE("program doesnt crash during work") {
  BST t;
  CHECK(t.insert(20));

  CHECK(t.remove(20));
}
