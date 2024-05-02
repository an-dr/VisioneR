cmake_minimum_required(VERSION 3.5)
project(visioner_base)

include(${CMAKE_CURRENT_LIST_DIR}/../../../ab.cmake)
add_component(visioner_base)
target_link_component(visioner_base ${CMAKE_CURRENT_LIST_DIR}/../microlog)
target_link_component(visioner_base ${CMAKE_CURRENT_LIST_DIR}/../object_finder)
target_link_component(visioner_base ${CMAKE_CURRENT_LIST_DIR}/../visioner_interfaces)
