cmake_minimum_required(VERSION 3.3)
project(NiceQueue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(NiceQueue ${SOURCE_FILES} NiceQueue.hpp NiceQueue.h NiceStack.hpp NiceStack.h)