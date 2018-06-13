cmake_minimum_required(VERSION 3.3)
project(DNARepair)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(DNARepair ${SOURCE_FILES} LinkedList.h LinkedList.hpp DNAElement.cpp DNAElement.h DNARepairer.cpp DNARepairer.h)