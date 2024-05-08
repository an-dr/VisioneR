cmake_minimum_required(VERSION 3.5)
project(visioner_base)

include(${CMAKE_CURRENT_LIST_DIR}/../../../ab.cmake)
add_component(visioner_base)
target_link_components(visioner_base ${CMAKE_CURRENT_LIST_DIR}/../microlog
                                     ${CMAKE_CURRENT_LIST_DIR}/../object_finder
                                     ${CMAKE_CURRENT_LIST_DIR}/../visioner_interfaces)
