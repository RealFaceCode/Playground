@page subExample1SerializerExample Serializer Example
@tableofcontents

@section section1SerializerExample Create an FS::Serializer
The code example shows how an FS::Serializer is created.
```c++
FS::Serializer sWrite("../Sandbox/test.txt");
```
@section section2SerializerExample Adding new nodes
To add a new node the function FS::Serializer::addNewNode() is used.
```c++
sWrite.addNewNode("newNode");
```

@section section3SerializerExample Adding data
To add data the function FS::Serializer::addDataToNode() is used.
```c++
sWrite.addDataToNode("newNode", 42);
```

@section section4SerializerExample Writing data to file
To write data to a file the function FS::Serializer::write() is used.
```c++
sWrite.write();
```

@section section5SerializerExample Loading data from file
To load data from a file the function FS::Serializer::load() is used.
```c++
FS::Serializer sLoad("../Sandbox/test.txt");
sLoad.load();
```

@section section6SerializerExample Getting data
To get data from the node the function FS::Serializer::getI32FromNode() is used. For all get functions take a look at FS::Serializer.
```c++
i32 value = sLoad("newNode");
```


@ref page1example "Examples"
@ref index "Playground"