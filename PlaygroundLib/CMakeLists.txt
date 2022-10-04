cmake_minimum_required(VERSION 3.19)
project(PlaygroundLib)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h")
file(GLOB_RECURSE GLAD_FILES "vendor/glad/*.cpp" "vendor/glad/*.hpp" "vendor/glad/*.c" "vendor/glad/*.h")
file(GLOB_RECURSE FHANDLE_FILES "vendor/fhandle/*.cpp" "vendor/fhandle/*.hpp" "vendor/fhandle/*.c" "vendor/fhandle/*.h")

include_directories("vendor/fhandle")
include_directories("vendor/glad")
include_directories("vendor/glm/glm/")
include_directories("vendor/stb/")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
add_compile_definitions(GLFW_INCLUDE_NONE)

add_library(PlaygroundLib ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})

target_link_libraries(PlaygroundLib glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(PlaygroundLib OpenGL::GL)