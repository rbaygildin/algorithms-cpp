cmake_minimum_required(VERSION 3.3)
project(StackMashine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(StackMashine ${SOURCE_FILES} IntStack.cpp IntStack.h StackMachine.cpp StackMachine.h)