cmake_minimum_required(VERSION 3.5)
project(FaceDesktop)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include(${CMAKE_CURRENT_LIST_DIR}/../../../ab.cmake)
add_component(${PROJECT_NAME})
target_link_components(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../visioner_interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

         
FILE(GLOB faces "components/universal_faces/png/*")
install (FILES ${faces} DESTINATION ./faces)
