@echo off
start getVendor.bat

mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
pause