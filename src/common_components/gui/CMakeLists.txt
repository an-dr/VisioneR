cmake_minimum_required(VERSION 3.5)
project(gui)

set(CMAKE_AUTOMOC ON) # for QT
find_package(Qt6 COMPONENTS Widgets REQUIRED)

include($ENV{ABCMAKE_PATH})
add_component(gui)

# add headers to sources so CMAKE_AUTOMOC can see them
target_sources(${PROJECT_NAME} PRIVATE src/MainWindow.hpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
