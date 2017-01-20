cmake_minimum_required(VERSION 3.5)
project(Suffix_Tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

set(SOURCE_FILES
        main.cpp)

add_executable(Repeticiones
        main.cpp)