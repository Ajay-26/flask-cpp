cmake_minimum_required(VERSION 3.15)

project(parallel_scheduler)

include_directories(
    inc
    )

file(GLOB SOURCES src/*/*.cpp)
set(SOURCES ${SOURCES} src/main.cpp)
add_executable(main ${SOURCES})