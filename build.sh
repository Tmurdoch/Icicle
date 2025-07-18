#!/bin/bash


if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	cmake -S . -B ./build -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  export VULKAN_SDK=~/Downloads/1.3.296.0/x86_64/
elif [[ "$OSTYPE" == "msys" ]]; then
	cmake -S . -B ./build -G "MSYS Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
fi

make -C ./build

