cmake_minimum_required(VERSION 3.15)
project(visioner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Qt
find_package(Qt5 COMPONENTS Widgets Core Gui Network PrintSupport REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5PrintSupport_INCLUDE_DIRS})


# Executable
add_executable(VisionerFile src/VisionerFile/main.cpp
                        src/App/App.cpp
                        src/App/ObjectFinder.cpp
                        src/VisionerFile/AppVisioner.cpp
                        src/VisionerFile/Face.cpp
                        src/VisionerFile/FileScanner.cpp
                        src/VisionerFile/InputFiles.cpp)
target_include_directories(VisionerFile PRIVATE src)
target_link_libraries(VisionerFile ${OpenCV_LIBS})


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
         
install (FILES lib/universal_faces/png/blink.png
               lib/universal_faces/png/calm.png
               lib/universal_faces/png/confused.png
               lib/universal_faces/png/happy.png
               lib/universal_faces/png/sad.png
               lib/universal_faces/png/thinking1.png
               lib/universal_faces/png/thinking2.png
               lib/universal_faces/png/thinking3.png
               lib/universal_faces/png/dunno.png
        DESTINATION ./faces)
