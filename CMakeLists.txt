cmake_minimum_required(VERSION 3.5)
project(Suffix_Tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0 -fpermissive")

set(SOURCE_FILES main.cpp)

add_subdirectory(src)

add_executable(Repeticiones main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(Repeticiones src)