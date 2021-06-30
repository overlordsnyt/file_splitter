# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.10.0)
project(practice1 C)
project(practice1 VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)
set(phone_generator phonegen)
set(splitter splitter)

add_executable(${phone_generator} random_phone_generator.c number.c)

target_link_libraries(${phone_generator} ${CMAKE_THREAD_LIBS_INIT})

add_executable(${splitter} split_file.c iocontrol.c)

target_link_libraries(${splitter} ${CMAKE_THREAD_LIBS_INIT})

add_executable(guess test_guess.c)

add_executable(guess2 test_guess2.c)