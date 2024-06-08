cmake_minimum_required(VERSION 3.5)
project(FaceDesktop)

# QT
set(CMAKE_AUTOMOC ON) # for QT
find_package(
    Qt6
    COMPONENTS Widgets
    REQUIRED
)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include($ENV{ABCMAKE_PATH})
add_component(${PROJECT_NAME})
target_link_components(${PROJECT_NAME} NAME visioner_interfaces gui)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} Qt6::Widgets)

file(GLOB faces "components/universal_faces/png/*")
install(FILES ${faces} DESTINATION ./faces)
