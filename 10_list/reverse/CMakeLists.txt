cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(reversell LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(doctest.cmake)
add_executable(tests test_reverse_ll.cpp)
target_link_libraries(tests PRIVATE doctest)
