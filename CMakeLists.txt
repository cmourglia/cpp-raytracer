cmake_minimum_required(VERSION 3.14)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_library(glad STATIC vendors/glad/src/glad.c)
target_include_directories(glad PUBLIC vendors/glad/include)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(vendors/glfw)

add_executable(${PROJECT_NAME} src/main.cpp src/boilerplate.cpp src/boilerplate.h)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)
