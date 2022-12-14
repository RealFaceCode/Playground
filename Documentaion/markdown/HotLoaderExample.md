@page subHotLoaderExample1 HotLoader  Example
@tableofcontents

In the example code:
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
The function HotLoader::AddFileToWatch() will be create a new HotLoader::FileWatch struct and the function HotLoader::CheckFiles() checks all HotLoader::FileWatch entries for modification.

The function HotLoader::IsModified() checks a specific file for a modification the function HotLoader::CheckFiles() has to be called! 

With the function HotLoader::GetFile() is a handle to a file accessible.

With the function HotLoader::RemoveFileToWatch() will a HotLoader::FileWatch be deleted.


@ref page1example "Examples"
@ref index "Playground"