cmake_minimum_required(VERSION 3.19)
project(Playground)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "Playground/src/*.cpp" "Playground/hdr/*.hpp" "Playground/src/*.c" "Playground/hdr/*.h" "Playground/main.cpp")
file(GLOB_RECURSE GLAD_FILES "PlayGround/vendor/glad/*.cpp" "PlayGround/vendor/glad/*.hpp" "PlayGround/vendor/glad/*.c" "PlayGround/vendor/glad/*.h")
file(GLOB_RECURSE FHANDLE_FILES "PlayGround/vendor/fhandle/*.cpp" "PlayGround/vendor/fhandle/*.hpp" "PlayGround/vendor/fhandle/*.c" "PlayGround/vendor/fhandle/*.h")

include_directories("Playground/vendor/fhandle")
include_directories("Playground/vendor/glad/include/")
include_directories("vendor/glm/glm/")
include_directories("vendor/stb/")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")

add_compile_definitions(GLFW_INCLUDE_NONE)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Playground ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})

target_link_libraries(Playground glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(Playground OpenGL::GL)