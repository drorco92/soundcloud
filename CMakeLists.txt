cmake_minimum_required(VERSION 3.15)
project(soundcloud)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DNDEBUG -Wall")

add_executable(soundcloud main.cpp AvlTree.h List.h)