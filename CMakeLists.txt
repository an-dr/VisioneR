cmake_minimum_required(VERSION 3.15)
project(visioner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
include(ab.cmake)
add_main_component(VisionerFile SOURCE_DIR "src/VisionerFile")
target_link_libraries(VisionerFile PRIVATE ${OpenCV_LIBS})

add_main_component(VisionerWebcam SOURCE_DIR "src/VisionerWebcam")
target_link_libraries(VisionerWebcam PRIVATE ${OpenCV_LIBS})

# Install
FILE(GLOB examples "img/examples/*")
install (FILES ${examples} DESTINATION ./input)
         
FILE(GLOB faces "components/universal_faces/png/*")
install (FILES ${faces} DESTINATION ./faces)
