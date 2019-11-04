cmake_minimum_required(VERSION 3.15)
project(Matriz_esparza)

set(CMAKE_CXX_STANDARD 17)

add_executable(Matriz_esparza main.cpp mocker/mocker.cpp mocker/mocker.h tester/tester.cpp tester/tester.h matrix.h node.h)