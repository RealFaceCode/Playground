cmake_minimum_required(VERSION 3.19)
project(Sandbox)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h" "main.cpp")
include_directories("../PlaygroundLib/hdr/")
include_directories("../PlaygroundLib/vendor/glad")
include_directories("../PlaygroundLib/vendor/fhandle")
include_directories("../PlaygroundLib/vendor/glm/glm/")
include_directories("../PlaygroundLib/vendor/stb/")
add_compile_definitions(GLFW_INCLUDE_NONE)

add_executable(Sandbox ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})
target_link_libraries(Sandbox PlaygroundLib)