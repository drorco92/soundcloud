cmake_minimum_required(VERSION 3.15)
project(soundcloud)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DNDEBUG -Wall")

add_executable(soundcloud  AvlTree.h List.h HashTable.h StreamNode.h Artist.h Artist.cpp Song.cpp library2.h
        SoundCloudSystem.cpp SoundCloudSystem.h)