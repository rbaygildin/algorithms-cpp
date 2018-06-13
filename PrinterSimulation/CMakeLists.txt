cmake_minimum_required(VERSION 3.3)
project(PrinterSimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(PrinterSimulation ${SOURCE_FILES} event.h event.cpp job.h job.cpp simulator.h simulator.cpp fifo.cpp fifo.h)