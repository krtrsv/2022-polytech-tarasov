cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(linkedlist LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(doctest.cmake)
add_executable(tests linked_list.cpp test_linked_list.cpp)
target_link_libraries(tests PRIVATE doctest)
