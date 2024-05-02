cmake_minimum_required(VERSION 3.15)
project(visioner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
add_definitions(-DULOG_HIDE_FILE_STRING)
add_definitions(-DULOG_SHORT_LEVEL_STRINGS)
add_definitions(-DULOG_USE_COLOR)
include(ab.cmake)

add_main_component(VisionerFile SOURCE_DIR "src/VisionerFile")
target_link_libraries(VisionerFile PRIVATE ${OpenCV_LIBS})
target_link_component(VisionerFile src/common_components/visioner_interfaces)
target_link_component(VisionerFile src/common_components/object_finder)
target_link_component(VisionerFile src/common_components/visioner_base)
target_link_component(VisionerFile src/common_components/microlog)

add_main_component(VisionerWebcam SOURCE_DIR "src/VisionerWebcam")
target_link_libraries(VisionerWebcam PRIVATE ${OpenCV_LIBS})
target_link_component(VisionerWebcam src/common_components/SceneReaderWebcam)
target_link_component(VisionerWebcam src/common_components/visioner_interfaces)
target_link_component(VisionerWebcam src/common_components/object_finder)
target_link_component(VisionerWebcam src/common_components/visioner_base)
target_link_component(VisionerWebcam src/common_components/microlog)


# Install
FILE(GLOB examples "img/examples/*")
install (FILES ${examples} DESTINATION ./input)
         
FILE(GLOB faces "components/universal_faces/png/*")
install (FILES ${faces} DESTINATION ./faces)
