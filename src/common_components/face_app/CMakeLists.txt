cmake_minimum_required(VERSION 3.5)
project(FaceApp)

include($ENV{ABCMAKE_PATH})
add_component(FaceApp)
target_link_components(FaceApp PATH ${CMAKE_CURRENT_LIST_DIR}/../common_components/eventpp
NAME visioner_interfaces)

target_link_libraries(${PROJECT_NAME} PRIVATE eventpp::eventpp)
