@echo off
git submodule init
git submodule update
cmake -S . -B build -G "MinGW Makefiles" -Dglew-cmake_BUILD_SHARED=OFF
pushd build
make
popd
