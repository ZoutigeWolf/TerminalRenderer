cmake_minimum_required(VERSION 3.29)
project(TerminalRenderer)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp
        lib/AsciiRenderer.cpp
        lib/AsciiRenderer.h
        lib/utils.cpp
        lib/utils.h
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})