#!/bin/sh

mkdir build
cd build
conan install ..
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake ..
cmake --build .