cmake_minimum_required(VERSION 3.5)
project (arithmetic_expressions)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weffc++ -g0 -Wall -Wextra -Wpedantic")

add_subdirectory(depends/Catch2)
include_directories(src)

add_subdirectory(src bin)

enable_testing()
add_subdirectory(test)
