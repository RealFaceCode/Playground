@page page1example Examples
@tableofcontents


@section section1Example Logger
A simple example for using the logger in playground.
````c++
#include "core.h"
#include "logger.h"

int main()
{
    CoreInit();
    LOG_INFO({}, "This is a info log message. %s", "And this is a value passed to the logger!")
    return EXIT_SUCCESS;
}
````
For more information:
- @subpage subExample1Logger "Logger Example"

@section section2Example Hot Loader

@section section3Example Memory leak tracker

@ref index "Playground"