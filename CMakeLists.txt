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
add_executable(visioner src/app.cpp
                        src/ObjectFinder.cpp
                        )
target_link_libraries(visioner ${OpenCV_LIBS} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Network_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
# target_link_options (visioner PRIVATE "$<$<BOOL:$<TARGET_PROPERTY:POSITION_INDEPENDENT_CODE>>:-fPIC>")


# Install
install(TARGETS visioner
        DESTINATION .)
install(FILES img/img_obj.jpg
              img/img_scene.jpg
              img/img_scene_obj.jpg
        DESTINATION .)
