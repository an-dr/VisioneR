cmake_minimum_required(VERSION 3.15)
project(VisionerWebcam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
add_definitions(-DULOG_HIDE_FILE_STRING)
add_definitions(-DULOG_SHORT_LEVEL_STRINGS)
add_definitions(-DULOG_USE_COLOR)
include(${CMAKE_CURRENT_LIST_DIR}/../../ab.cmake)

add_main_component(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/SceneReaderWebcam)
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_interfaces)
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/object_finder)
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_base)
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/microlog)
target_link_component(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../common_components/FaceDesktop)

# Install
FILE(GLOB examples "img/examples/*")
install (FILES ${examples} DESTINATION ./input)
