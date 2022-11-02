#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "students.h"
#include <doctest.h>
#include <iostream>

auto example_stud = Student{"x", -999};

auto example_sl() -> StudentList {
  class StudentList sl = {{"first", 10}, {"second", 5}, {"third", 0}};
  return sl;
}

TEST_CASE("yo") {
  CHECK_EQ(Student{"subject", 10}, Student{"subject", 10});

  CHECK_EQ(example_sl()
               .append("v", 999)
               .append(example_stud)
               .remove("first")
               .remove("third")
               .remove("second"),
           StudentList{{"v", 999}, {"x", -999}});

  CHECK_EQ(example_sl().get_avg_score(), 5);

  CHECK_EQ(example_sl().get_best_students(), StudentList{{"first", 10}});

  CHECK_EQ(example_sl().get_worst_students(), StudentList{{"third", 0}});

  CHECK_EQ(example_sl().set_score("third", 50).find_student("third").score, 50);
}
