# Icicle: A Dedicated Game Engine for Real-Time Strategy
Welcome to the Icicle game engine repository! This engine is designed to cater to the specific needs of real-time strategy (RTS) type video games. This project is still underway and is not ready for gameplay implementation yet. 

As of now Icicle works on both Windows and Linux (Ubuntu 22).


### Technologies/Libraries used:

Icicle leverages the following technologies and libraries to ensure a robust development environment:
- [MINGW-64](https://code.visualstudio.com/docs/cpp/config-mingw "MINGW-64") for VScode, using gcc, gdb, g++ version 13.1
- [catch2](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top) for testing, 



## Building the project

#### Windows 
- use 'cmake -S [source_dir] -B [build_dir] -G "MSYS Makefiles"' to build if using msys version of make
- then make all

#### Linux 
- CMake for build: 
    1. use 'cmake -S . -B build' #builds into build/ diretory
    2. then cd into build and make all


 ## Testing
- CMake for tests: 
    1. cd into Tests directory and run cmake -S .
    2. make all
    3. executable will be called "out"


The decision not to employ game engines like Unity or Unreal was driven by the need to have greater autonomy in optimizing performance, particularly in the face of challenging real-time strategy (RTS) elements.
