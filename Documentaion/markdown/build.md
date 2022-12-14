@page page1build Build
@tableofcontents

@section section1build CMAKE
This shows the code to implement this library in to your application.
```cmake
cmake_minimum_required(VERSION 3.20)
project(ExampleProject)
set(CMAKE_CXX_STANDARD 20)

include_directories(vendor/Playground/PlaygroundLib/hdr)
add_subdirectory(vendor/Playground/PlaygroundLib)

add_executable(ExampleProject main.cpp)
target_link_libraries(ExampleProject PlaygroundLib)
```

@ref index "Playground"