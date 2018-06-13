cmake_minimum_required(VERSION 3.3)
project(PointArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(PointArray ${SOURCE_FILES} geometry.cpp geometry.h)