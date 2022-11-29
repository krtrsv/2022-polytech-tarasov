#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "linked_list.hpp"
#include <doctest.h>

TEST_CASE("Elements can be inserted") {
  LinkedList<int> ll{1, 2, 3, 4, 5};

  REQUIRE(ll.size() == 5);

  ll.insert(2, 9);
  CHECK(ll == LinkedList{1, 2, 9, 3, 4, 5});

  ll.insert(0, 8);
  CHECK(ll == LinkedList<int>{8, 1, 2, 9, 3, 4, 5});

  ll.insert(7, 7);
  CHECK(ll == LinkedList<int>{8, 1, 2, 9, 3, 4, 5, 7});

  REQUIRE(ll.size() == 8);
}

TEST_CASE("Elements can be removed") {
  LinkedList<int> ll{8, 1, 2, 9, 3, 4, 5, 7};

  ll.remove(3);
  CHECK(ll == LinkedList<int>{8, 1, 2, 3, 4, 5, 7});

  ll.remove(0);
  CHECK(ll == LinkedList<int>{1, 2, 3, 4, 5, 7});

  ll.remove(5);
  CHECK(ll == LinkedList<int>{1, 2, 3, 4, 5});

  REQUIRE(ll.size() == 5);
}

TEST_CASE("Deleting/pasting elements outside the array does nothing") {
  LinkedList<int> ll{1, 2, 3, 4, 5};

  REQUIRE(ll.insert(99, 0) == false);
  CHECK(ll == LinkedList{1, 2, 3, 4, 5});

  REQUIRE(ll.remove(99) == false);
  CHECK(ll == LinkedList{1, 2, 3, 4, 5});
}

TEST_CASE("Getting elements by index") {
  LinkedList<int> ll{1, 2, 3, 4, 5};

  CHECK(ll.get(0)->data == 1);
  CHECK(ll.get(2)->data == 3);
  CHECK(ll.get(4)->data == 5);
  CHECK(ll.get(99) == nullptr);
}

TEST_CASE("Deep copying") {
  LinkedList<int> ll{1, 2, 3, 4, 5};
  LinkedList<int> ll_cloned;

  ll.clone(&ll_cloned);

  CHECK(ll == ll_cloned);
}
