# Icicle
Game engine for RTS type video games

Technologies/Libraries used:
- opengl
- math library TBD
- MYSYS2 (Cmake, gcc) https://code.visualstudio.com/docs/cpp/config-mingw
- doctest for testing, https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md


C++ reference: https://en.cppreference.com/w/

Using gcc, gdb, g++ version 13.1

use : cmake -G "MSYS Makefiles" .. to build if using msys version of make
Note: will not work on cmd??

****Linux 
- CMake for build: 
    1. use Cmake -S . -B build #builds into build/ diretory
    2. then cd into build and make all
- CMake for tests: 
    1. cd into Tests directory and run CMake -S .
    2. make all
    3. executable will be called "out"