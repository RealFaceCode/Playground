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
This code shows how the HotLoader is used.
```c++
#include "core.h"
#include "util/hotloader.h"

int main(int argc, char** argv)
{
    CoreInit();
    HotLoader::AddFileToWatch("../Sandbox/main.cpp");
    while(!HotLoader::IsModified("../Sandbox/main.cpp"))
    {
        HotLoader::CheckFiles();
    }
    auto file = HotLoader::GetFile("../Sandbox/main.cpp");
    HotLoader::RemoveFileToWatch("../Sandbox/main.cpp");
    return EXIT_SUCCESS;
}
```

For more information:
- @subpage subHotLoaderExample1 "HotLoader Example"
@section section3Example Memory leak tracker

@ref index "Playground"