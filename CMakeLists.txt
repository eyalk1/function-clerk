cmake_minimum_required(VERSION 3.16)

project("clerk")

set(CXX_STANDARD C++20)

add_executable(example 
                examples/funman.cpp)

set_property(TARGET example PROPERTY CXX_STANDARD 20)

target_include_directories(example PUBLIC ./include)