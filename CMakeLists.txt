cmake_minimum_required(VERSION 3.15)
project(visioner)

include(ab.cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
add_executable(VisionerFile src/VisionerFile/main.cpp
                            src/VisionerFile/AppVisioner.cpp
                            src/VisionerFile/Face.cpp
                            src/VisionerFile/FileScanner.cpp
                            src/VisionerFile/InputFiles.cpp)
target_link_libraries(VisionerFile PRIVATE ${OpenCV_LIBS})
target_init_abcmake(VisionerFile)


# Install
install(TARGETS VisionerFile
        DESTINATION .)
        
install (FILES img/examples/object_good_1.jpg
               img/examples/object_bad_1.jpg
               img/examples/scene_1.jpg
               img/examples/scene_2.jpg
               img/examples/scene_3.jpg
               img/examples/scene_4.jpg
         DESTINATION ./input)
         
install (FILES components/universal_faces/png/blink.png
               components/universal_faces/png/calm.png
               components/universal_faces/png/confused.png
               components/universal_faces/png/happy.png
               components/universal_faces/png/sad.png
               components/universal_faces/png/thinking1.png
               components/universal_faces/png/thinking2.png
               components/universal_faces/png/thinking3.png
               components/universal_faces/png/dunno.png
        DESTINATION ./faces)
