cmake_minimum_required(VERSION 3.19)
project(PlaygroundLib)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE folder_contents "vendor/glm*" "vendor/glfw*" "vendor/stb*")
if (!folder_contents)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        execute_process(COMMAND "getVendor.bat"
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output
                ERROR_VARIABLE error)
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        message(STATUS "Platform: Linux")
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        message(STATUS "Platform: macOS")
    else()
        message(STATUS "Unknown platform")
    endif()

    if (result EQUAL 0)
        message(STATUS "Batch file executed successfully")
    else()
        message(ERROR "Error while executing batch file: ${error}")
    endif()
endif()

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h")
file(GLOB_RECURSE GLAD_FILES "vendor/glad/*.cpp" "vendor/glad/*.hpp" "vendor/glad/*.c" "vendor/glad/*.h")
file(GLOB_RECURSE FHANDLE_FILES "vendor/fhandle/*.cpp" "vendor/fhandle/*.hpp" "vendor/fhandle/*.c" "vendor/fhandle/*.h")

include_directories(vendor/fhandle vendor/glad vendor/glm/glm/ vendor/stb/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
add_compile_definitions(GLFW_INCLUDE_NONE)

add_library(PlaygroundLib ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES})
target_include_directories(PlaygroundLib PUBLIC vendor/glm/glm/ vendor/fhandle/ vendor/glad/ vendor/stb/)
target_compile_definitions(PlaygroundLib PUBLIC GLFW_INCLUDE_NONE)

target_link_libraries(PlaygroundLib glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(PlaygroundLib OpenGL::GL)