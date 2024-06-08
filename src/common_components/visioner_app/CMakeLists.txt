cmake_minimum_required(VERSION 3.5)
project(visioner_app)

set(CMAKE_AUTOMOC ON) # for QT
find_package(
    Qt6
    COMPONENTS Widgets
    REQUIRED
)

include($ENV{ABCMAKE_PATH})
add_component(visioner_app)

target_link_components(visioner_app NAME gui microlog visioner_interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
