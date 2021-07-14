cmake_minimum_required(VERSION 3.16)

project("clerk")

set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_C_COMPILER /usr/bin/g++-10)

add_executable(example "funman.cpp")

set_property(TARGET example PROPERTY CXX_STANDARD 20)

target_include_directories(example PUBLIC ./src)