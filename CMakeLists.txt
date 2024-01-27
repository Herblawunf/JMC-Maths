cmake_minimum_required(VERSION 3.27)
project(la)

set(CMAKE_CXX_STANDARD 17)

add_executable(la src/main.cpp
        src/matrix.cpp
        src/operations.cpp
        include/columnVector.h
        src/columnVector.cpp
        src/utilities.cpp
        include/linearEquation.h
        src/linearEquation.cpp
        include/LinearSystem.h
        src/LinearSystem.cpp
        src/vectorSets.cpp)
