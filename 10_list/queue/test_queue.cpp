#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "queue.hpp"
#include <doctest.h>

TEST_CASE("?") {
  Node *head = new Node(1, nullptr);

  enqueue(&head, 2);
  CHECK(dequeue(&head) == std::pair{OK, 2});
  CHECK(dequeue(&head) == std::pair{OK, 1});
  CHECK(dequeue(&head) == std::pair{EMPTY, 0});
}
