cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(students LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(doctest.cmake)
add_executable(tests.out test_students.cpp)
target_link_libraries(tests.out PRIVATE doctest)
