@page subExample1MemoryLeakTrackerExample Memory leak tracker Example
@tableofcontents

@section section1MemoryLeakTrackerExample Enable / Disable
With the function MemoryEnableTracking() can be the tracking be enabled or disabled.
```c++
MemoryEnableTracking(true);     //enabled
MemoryEnableTracking(false);    //disabled
```
@note The standard value is set to false!

@section section2MemoryLeakTrackerExample Allocating
With the MACRO Malloc() can be a memory section be allocated.
```c++
int* array1 = (int*)Malloc(8); //allocated enough space for an integer
```
And with the MACRO Realloc() can a memory section be reallocated.
```c++
array1 = (int*)Realloc(16); //allocated enough space for two integer
```

@section section3MemoryLeakTrackerExample Register / Deregister
With the MACRO MemReg can an extern pointer be registered.
```c++
int* i = new int[1];
i = (int*)MemReg(i);
```
And with the MACRO MemDeReg() can an extern pointer be degistered.
```c++
MemDeReg(i);
```
@section section4MemoryLeakTrackerExample Deallocating
With the MACRO Free() can a memory section be deallocated.
```c++
Free(array1);
```
@ref page1example "Examples"
@ref index "Playground"