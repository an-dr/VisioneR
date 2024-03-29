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
add_executable(visioner src/main.cpp
                        src/App/App.cpp
                        src/Visioner/AppVisioner.cpp
                        src/App/ObjectFinder.cpp
                        src/Visioner/Face.cpp
                        src/Visioner/FileScanner.cpp
                        src/Visioner/InputFiles.cpp
                        )
target_include_directories(visioner PRIVATE src)
target_link_libraries(visioner ${OpenCV_LIBS} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Network_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
# target_link_options (visioner PRIVATE "$<$<BOOL:$<TARGET_PROPERTY:POSITION_INDEPENDENT_CODE>>:-fPIC>")


# Install
install(TARGETS visioner
        DESTINATION .)
install(FILES img/img_obj.jpg
              img/img_scene.jpg
              img/img_scene_many.jpg
              img/img_scene_obj.jpg
        DESTINATION .)
        
install (FILES img/examples/object_good_1.jpg
               img/examples/object_bad_1.jpg
               img/examples/scene_1.jpg
               img/examples/scene_2.jpg
               img/examples/scene_3.jpg
               img/examples/scene_4.jpg
         DESTINATION ./input)
         
install (FILES assets/png/blink.png
               assets/png/calm.png
               assets/png/confused.png
               assets/png/happy.png
               assets/png/sad.png
               assets/png/thinking1.png
               assets/png/thinking2.png
               assets/png/thinking3.png
               assets/png/dunno.png
        DESTINATION ./assets)
