cmake_minimum_required(VERSION 3.15)
project(SceneReaderWebcam)

include(${CMAKE_CURRENT_LIST_DIR}/../../../ab.cmake)
add_component(${PROJECT_NAME} SOURCE_DIR "."
                              INCLUDE_DIR ".")
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../visioner_interfaces)
