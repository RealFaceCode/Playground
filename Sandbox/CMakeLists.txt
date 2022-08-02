cmake_minimum_required(VERSION 3.19)
project(Sandbox)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h" "main.cpp")
file(GLOB_RECURSE GLAD_FILES "../vendor/glad/*.cpp" "../vendor/glad/*.hpp" "../vendor/glad/*.c" "../vendor/glad/*.h")
file(GLOB_RECURSE FHANDLE_FILES "../vendor/fhandle/*.cpp" "../vendor/fhandle/*.hpp" "../vendor/fhandle/*.c" "../vendor/fhandle/*.h")

include_directories("../PlaygroundLib/hdr/")

add_executable(Sandbox ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})

target_link_libraries(Sandbox PlaygroundLib)