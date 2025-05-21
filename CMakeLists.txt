cmake_minimum_required(VERSION 3.28)
project(poly_ref)

set(CMAKE_CXX_STANDARD 20)

add_executable(poly_ref main.cpp
        Polynomial.h
        Polynomial.cpp
        Z3.h
        Z3.cpp
)
