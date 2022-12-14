@page page1build Build
@tableofcontents

@section section1build CMAKE
This shows the code to implement this library in to your application.
```cmake
cmake_minimum_required(VERSION 3.19)
project(Sandbox)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h" "main.cpp")

include_directories("../PlaygroundLib/hdr/")

add_executable(Sandbox ${SOURCE_FILES})
target_link_libraries(Sandbox PlaygroundLib)
```

@ref index "Playground"