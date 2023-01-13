cmake_minimum_required(VERSION 3.19)
project(PlaygroundLib)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h")
file(GLOB_RECURSE GLAD_FILES "vendor/glad/*.cpp" "vendor/glad/*.hpp" "vendor/glad/*.c" "vendor/glad/*.h")
file(GLOB_RECURSE FHANDLE_FILES "vendor/fhandle/*.cpp" "vendor/fhandle/*.hpp" "vendor/fhandle/*.c" "vendor/fhandle/*.h")

include_directories(vendor/fhandle vendor/glad vendor/glm/glm/ vendor/stb/ vendor/openal-soft/include/ vendor/lua/src/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory("vendor/openal-soft")
add_subdirectory("vendor/lua")

add_library(PlaygroundLib ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})

target_include_directories(PlaygroundLib PUBLIC vendor/glm/glm/ vendor/fhandle/ vendor/glad/ vendor/stb/ vendor/openal-soft/include/ vendor/lua/src/)
target_compile_definitions(PlaygroundLib PUBLIC GLFW_INCLUDE_NONE)

find_package(OpenGL REQUIRED)
target_link_libraries(PlaygroundLib OpenGL::GL glfw OpenAL LUA)