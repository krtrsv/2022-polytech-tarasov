#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "students.h"
#include <iostream>

auto s1 = Student{"first", 10};
auto s2 = Student{"second", 5};
auto s3 = Student{"third", 0};
StudentList sl;
StudentList sl_il{s1, s2, s3};
StudentList slb{s1};
StudentList slw{s3};
StudentList slwf{s2, s3};

TEST_CASE("yo") {
  CHECK_EQ(Student{"first", 10}, Student{"first", 10});
  CHECK_EQ(sl.append(s1).append(s2).append(s3), sl_il);
  CHECK_EQ(sl.get_avg_score(), 5);
  CHECK_EQ(sl.get_best_students(), slb);
  CHECK_EQ(sl.get_worst_students(), slw);
  CHECK_EQ(sl.remove(s1), slwf);
  CHECK_EQ(sl.set_score("third", 50).find_student("third").score, 50);
}
