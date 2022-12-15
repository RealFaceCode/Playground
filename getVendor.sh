#!/bin/bash

echo "Cloning repositories..."
cd PlaygroundLib || exit
mkdir vendor
cd vendor || exit

git clone https://github.com/glfw/glfw.git
git clone https://github.com/g-truc/glm.git
git clone https://github.com/nothings/stb.git
git clone https://github.com/kcat/openal-soft.git