cmake_minimum_required(VERSION 3.5)
project(visioner_app)

include($ENV{ABCMAKE_PATH})
add_component(visioner_app)
target_link_components(visioner_app PATH ${CMAKE_CURRENT_LIST_DIR}/../common_components/eventpp
                                    NAME microlog FaceApp visioner_interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE eventpp::eventpp)
