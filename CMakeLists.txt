cmake_minimum_required(VERSION 3.29)
project(COMP345project)

set(CMAKE_CXX_STANDARD 20)

add_executable(COMP345project main.cpp
        Critter.cpp
        Critter.h
        CritterGroupGenerator.cpp
        CritterGroupGenerator.h)
