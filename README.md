# Icicle: A Dedicated Game Engine for Real-Time Strategy
Welcome to the Icicle game engine repository! This engine is designed to cater to the specific needs of real-time strategy (RTS) type video games. This project is still underway and is not ready for gameplay implementation yet. 

As of now Icicle works on both Windows and Linux (Ubuntu 22).


### Technologies/Libraries used:

Icicle leverages the following technologies and libraries:
- [CMake](https://cmake.org/) - and generator of some sort. Visual Studio should handle this automatically using ninja. Other options are MinGW, Msvc, these will need to be specified with -G option when first building the project. No guarantee that any other generators work other than Ninja and Unix Makefiles. These are the currently supported options.
- [catch2](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top) for testing, 
- [Visual Studio](https://visualstudio.microsoft.com/) - Nice because it 
integrates with CMake very well and theres no need to specify a generator, VS 
should handle this automatically

## Goals
- Performant
- Fast development for use in game jams (this will require editors probably - TBD)


##  Prerequsite installs:
C++ compiler
Vulkan - see the vulkan website
GLFW - see https://www.glfw.org/docs/3.3/compile.html for install instructions
    - source files are in lib/glfw
`sudo apt install vulkan-validationlayers`

## Building the project examples

#### Windows

install make for windows: https://gnuwin32.sourceforge.net/packages/make.htm, 
add the folder above make.exe to the path

Recompile the libraries for windows
    - for glfw, cd into glfw and run cmake .
    this will generate the following files:
        lib/glfw/src/glfw3.pc
        lib/glfw/src/glfw_config.h

- use (if using msys):
```
cmake -S [source_dir] -B [build_dir] -G "MSYS Makefiles"
```
- then make all

#### Linux (Make)
CD into project rootu directory. Make sure to delete CmakeCache and CmakeFiles directory before building if you have previously used a different Generator. 
- CMake for build: 
    1. use
```'cmake -S . -B [build directory] -G "Unix Makefiles"``` #builds into build/ diretory
    2. then cd into build and make all
    3. cd in into build and run executable
