#!/bin/sh
export TOOLCHAIN_PATH=$(dirname $0)
export TOOLCHAIN_FILE=$TOOLCHAIN_PATH/hisi-linux.cmake
export ROOT_PATH=/opt/hisi-linux/x86-arm/gcc-3.4.3-uClibc-0.9.28
export PATH=$ROOT_PATH/bin:$PATH
export CC=arm-linux-gcc
export CXX=arm-linux-g++
export SDLDIR=$ROOT_PATH
export HISILICON=1
make
