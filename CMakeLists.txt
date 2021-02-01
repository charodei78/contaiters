cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED on)
add_subdirectory(Google_tests)

add_executable(Test main.cpp Vector.hpp Stack.hpp)
