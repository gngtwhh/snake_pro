cmake_minimum_required(VERSION 3.25)
project(贪吃蛇_多玩法)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
file(GLOB ALL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)
add_executable(snake_plus ${ALL_SOURCES})
