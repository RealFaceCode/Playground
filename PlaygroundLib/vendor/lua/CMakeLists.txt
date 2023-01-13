cmake_minimum_required(VERSION 3.19)
project(LUA)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")

add_library(LUA ${SOURCE_FILES})
target_include_directories(LUA PUBLIC src/)