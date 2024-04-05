@echo off
cmake -S . -B build -G "MinGW Makefiles"
pushd build
make
popd
