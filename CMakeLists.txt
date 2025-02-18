cmake_minimum_required(VERSION 3.10)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_subdirectory(Creational)
add_subdirectory(Structural)
add_subdirectory(Behavioral)

