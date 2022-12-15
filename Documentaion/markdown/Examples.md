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

@section section2Example HotLoader
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
This code shows how the memory leak tracker is used.
```c++
#include "core.h"
#include "util/memory.h"

int main(int argc, char** argv)
{
CoreInit();
MemoryEnableTracking(true);
int* array1 = (int*)Malloc(8);
int* array2 = (int*)Malloc(8);              //memory leak is never freed
int* array3 = (int*)MemReg(new int[1]);
int* array4 = (int*)MemReg(new int[1]);     //memory leak is never freed

MemZero(array1, 8);
MemZero(array2, 8);
MemZero(array3, 8);
MemZero(array4, 8);

MemDeReg(array3);
Free(array1);
return EXIT_SUCCESS;
}
```

For more information:
- @subpage subExample1MemoryLeakTrackerExample "Memory leak tracker Example"

@section section4Example String
This simple example shows how a string is used.
```c++
#include "core.h"
#include "util/buffer/string.h"

int main(int argc, char** argv)
{
    CoreInit();
    String string("im a string");
    string.add(". I was added later!");
    return EXIT_SUCCESS;
}
```

For more information:
- @subpage subExample1StringExample "String Example"

@section section5Example File

For more information:
- @subpage subExample1FileExample "File Example"

@section section6Example Serializer
This example shows how the FS::Serializer should be used.
```c++
#include "core.h"
#include "util/FileStream.h"

int main(int argc, char** argv)
{
    CoreInit();
    
    FS::Serializer s("../Sandbox/test.txt");
    s.addNewNode("i/am/a/new/node");
    s.addDataToNode("i", "1");
    s.addDataToNode("i/am", "2");
    s.addDataToNode("i/am/a", "3");
    s.addDataToNode("i/am/a/new", "4");
    s.addDataToNode("i/am/a/new/node", "5");
    s.write();

    FS::Serializer s2("../Sandbox/test.txt");
    s2.load();
    int ir1 = s2.getI32FromNode("i");
    int ir2 = s2.getI32FromNode("i/am");
    int ir3 = s2.getI32FromNode("i/am/a");
    int ir4 = s2.getI32FromNode("i/am/a/new");
    int ir5 = s2.getI32FromNode("i/am/a/new/node");

    return EXIT_SUCCESS;
}
```

For more information:
- @subpage subExample1SerializerExample "Serializer Example"


@ref index "Playground"