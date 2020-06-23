cmake_minimum_required(VERSION 3.16)
project(Snowing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Snowing WIN32 Snowing.cpp)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(Snowing ${OPENGL_LIBRARIES})