cmake_minimum_required(VERSION 3.3)
project(Cities)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Cities ${SOURCE_FILES} City.h RailSystem.cpp RailSystem.h Service.h)