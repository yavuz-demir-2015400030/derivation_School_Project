cmake_minimum_required(VERSION 2.8)
project(project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Variable.cpp Variable.h Function.cpp Function.h Graph.h Graph.cpp)
add_executable(project4 ${SOURCE_FILES})