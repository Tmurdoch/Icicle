# Icicle: A Dedicated Game Engine for Real-Time Strategy
Welcome to the Icicle game engine repository! This engine is designed to cater to the specific needs of real-time strategy (RTS) type video games. This project is still underway and is not ready for gameplay implementation yet. 

As of now Icicle works on both Windows and Linux (Ubuntu 22).


### Technologies/Libraries used:

Icicle leverages the following technologies and libraries to ensure a robust development environment:
- [CMake](https://cmake.org/) - and generator of some sort. Visual Studio should handle this automatically using ninja. Other options are MinGW, Msvc, these will need to be specified with -G option when first building the project
- [catch2](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top) for testing, 



## Building the project examples

#### Windows 
- use 'cmake -S [source_dir] -B [build_dir] -G "MSYS Makefiles"' to build if using msys version of make
- then make all

#### Linux (Make)
Make sure delete CmakeCache and CmakeFiles directory before building
- CMake for build: 
    1. use 'cmake -S . -B build' -G "Unix Makefiles" #builds into build/ diretory
    2. then cd into build and make all


The decision not to employ game engines like Unity or Unreal was driven by the need to have greater autonomy in optimizing performance, particularly in the face of challenging real-time strategy (RTS) elements.
