cmake_minimum_required(VERSION 3.17)

project(c___HW1)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined,address")

add_executable(matrix main.cpp matrices.hpp matrices.cpp)