@echo off
cd PlaygroundLib
mkdir vendor
cd vendor

start git clone https://github.com/glfw/glfw.git
start git clone https://github.com/g-truc/glm.git
start git clone https://github.com/nothings/stb.git
start git clone https://github.com/kcat/openal-soft.git