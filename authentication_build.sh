#!/bin/bash
mkdir build
mkdir modules
cp authentication.cmake CMakeLists.txt
cd build
cmake ..
make
cp libauthentication.* ../modules/
cd ..
rm -r build
rm CMakeLists.txt