#!/bin/bash

git submodule init
git submodule update
cd build
cmake -S ..
make
cd ..
