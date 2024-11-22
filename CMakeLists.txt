cmake_minimum_required(VERSION 3.29)
project(HashMapProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(HashMapProject
        hashNode.hpp
        hashMap.hpp
        makeSeuss.hpp
        makeSeuss.cpp
        hashNode.cpp
        hashMap.cpp
        lab7main.cpp)
