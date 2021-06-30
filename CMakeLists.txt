# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.10.0)
project(practice1 C)
project(practice1 VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

    if (MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif ()

endif ()

find_package(Threads REQUIRED)
set(phone_generator phonegen)
set(splitter splitter)

#phone_generator是一行一号码的电话号码txt文件生成器

add_executable(${phone_generator} random_phone_generator.c number.c)

target_link_libraries(${phone_generator} ${CMAKE_THREAD_LIBS_INIT})

#splitter是根据命令行参数，指定行数，分割大txt成小txt的分割工具

add_executable(${splitter} split_file.c iocontrol.c)

target_link_libraries(${splitter} ${CMAKE_THREAD_LIBS_INIT})

#guess是关于C语言的想法测试和演练程序

add_executable(guess test_guess.c)

add_executable(guess2 test_guess2.c)

target_link_libraries(guess2 ${CMAKE_THREAD_LIBS_INIT})