cmake_minimum_required(VERSION 3.19)
project(PlaygroundLib)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
add_compile_definitions(GLFW_INCLUDE_NONE)

include_directories("vendor/fhandle")
include_directories("vendor/glad/include/")
include_directories("vendor/glm/glm/")

add_subdirectory(PlaygroundLib)
add_subdirectory(Sandbox)