cmake_minimum_required(VERSION 3.15)
project(VisionerFile)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) # for QT
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
add_definitions(-DULOG_HIDE_FILE_STRING)
add_definitions(-DULOG_SHORT_LEVEL_STRINGS)
add_definitions(-DULOG_USE_COLOR)

# Add abcmake
set(ENV{ABCMAKE_PATH} ${CMAKE_CURRENT_LIST_DIR}/../../ab.cmake)
include($ENV{ABCMAKE_PATH})

add_main_component(${PROJECT_NAME})

register_components(${CMAKE_CURRENT_LIST_DIR}/../common_components/microlog
                    ${CMAKE_CURRENT_LIST_DIR}/../common_components/gui
                    ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_interfaces
                    ${CMAKE_CURRENT_LIST_DIR}/../common_components/face_app
                    ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_app
                    ${CMAKE_CURRENT_LIST_DIR}/../common_components/FaceDesktop
                    )

target_link_components(${PROJECT_NAME} PATH ${CMAKE_CURRENT_LIST_DIR}/../common_components/eventpp
                                       NAME visioner_interfaces 
                                            visioner_app 
                                            microlog 
                                            gui
                                            FaceApp
                                            FaceDesktop)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS}
                                              Qt6::Widgets
                                              eventpp::eventpp)

# Install examples
FILE(GLOB examples "${CMAKE_CURRENT_LIST_DIR}/../../img/examples/*")
install (FILES ${examples} DESTINATION ./input)

