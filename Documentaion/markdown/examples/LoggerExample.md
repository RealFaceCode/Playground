@page subExample1Logger Logger Example
@tableofcontents

@section section1LoggingExample Highlighting
For creating a Highlight the MARCO C_HiLi() is used.

The first argument is a String, this tells which should be highlighted.

The second argument is an #ConsoleOutPutColor, this tells which color the highlighted section should have.

The third argument is an index value, this is there to select the right one if there are several matches.
````c++
C_HiLI("something to highlight", Yellow, 0)
````
For the color input is the enum #ConsoleOutPutColor used.

@section section2LoggingExample Logging calls
All available logging calls are:

- LOG_INFO();
- LOG_WARNING();
- LOG_ERROR();
- LOG_ASSERT();

```c++
LOG_INFO({}, "some log);
LOG_WARNING({}, "some log);
LOG_ERROR({}, "some log);
LOG_ASSERT(false, {}, "some log");
```

@section section3LoggingExample Using a highlight
This shows how to use highlights
````c++
LOG_INFO({C_HiLi("highlight", Yellow, 0)}, "something has a highlight"})
````

@ref page1example "Examples"
@ref index "Playground"