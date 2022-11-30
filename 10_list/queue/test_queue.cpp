#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "queue.hpp"
#include <doctest.h>

TEST_CASE("?") {

  Queue q;

  q.enqueue(1);
  q.enqueue(2);
  q.dequeue();
  q.dequeue();
  q.enqueue(3);
  q.enqueue(4);
  q.enqueue(5);
  q.dequeue();
  CHECK((q.front)->data == 4);
  CHECK((q.rear)->data == 5);
}
