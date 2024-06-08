cmake_minimum_required(VERSION 3.15)
project(SceneReaderWebcam)

include($ENV{ABCMAKE_PATH})
add_component(${PROJECT_NAME} SOURCE_DIR "." INCLUDE_DIR ".")
target_link_components(
    ${PROJECT_NAME} PATH ${CMAKE_CURRENT_LIST_DIR}/../visioner_interfaces
)
