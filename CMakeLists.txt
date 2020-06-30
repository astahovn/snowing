cmake_minimum_required(VERSION 3.16)
project(Snowing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Snowing WIN32 src/Snowing.cpp src/App.h src/App.cpp src/Window/IWindow.h src/Window/Win32.cpp src/Window/Win32.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(Snowing ${OPENGL_LIBRARIES})