cmake_minimum_required(VERSION 3.3)
project(SafeArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/egdeveloper/Documents/Clion Projects/Binaries/")
set(SOURCE_FILES main.cpp)
add_executable(SafeArray ${SOURCE_FILES} safearray.h course.h)