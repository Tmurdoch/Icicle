#!/bin/sh


if [["$OSTYPE" == "linux-gnu"* ]]; then
	cmake -S . -B ./build -G "Unix Makefiles"
elif [["$OSTYPE" == "msys" ]]; then
	cmake -S . -B ./build -G "MSYS Makefiles"
fi

make -C ./build

