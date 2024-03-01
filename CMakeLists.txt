cmake_minimum_required(VERSION 3.15)
project(visioner)

set(CMAKE_CXX_STANDARD 17)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
add_executable(visioner src/app.cpp)
target_link_libraries(visioner ${OpenCV_LIBS})

# Install
install(TARGETS visioner
        DESTINATION .)
# install(FILES src/hello.cpp DESTINATION src)
