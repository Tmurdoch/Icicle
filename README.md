# Icicle
Game engine for RTS type video games


The reason I did not use a game engine like Unity or Unreal is for freedom of optimization when the RTS elements become difficult. 

Technologies/Libraries used:
- [MINGW-64](https://code.visualstudio.com/docs/cpp/config-mingw "MYSYS2") for VScode, using gcc, gdb, g++ version 13.1
- [doctest](https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md) for testing, 



## Building the project

Windows 
- cmake -G "MSYS Makefiles" .. to build if using msys version of make
- then make all

Linux 
- CMake for build: 
    1. use cmake -S . -B build #builds into build/ diretory
    2. then cd into build and make all


 ### Testing
- CMake for tests: 
    1. cd into Tests directory and run cmake -S .
    2. make all
    3. executable will be called "out"
