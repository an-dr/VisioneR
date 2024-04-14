cmake_minimum_required(VERSION 3.5)

include(ab.cmake)

project(visioner_base)
add_library(${PROJECT_NAME})
target_init_abcmake(${PROJECT_NAME})
