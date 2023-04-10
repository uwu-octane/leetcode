cmake_minimum_required(VERSION 3.21)
project(Leetcodes)

set(CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD})

# Create a library target with the LC05.cpp file
add_library(SolutionsLib STATIC solution.h LC05.cpp LC05.h LC06.cpp LC06.h LC07.cpp)