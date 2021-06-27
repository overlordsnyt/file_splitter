# cmake_minimum_required(VERSION <specify CMake version here>)
project(practice1 C)

set(CMAKE_C_STANDARD 11)

add_executable(practice1 main.c number.c number.h)