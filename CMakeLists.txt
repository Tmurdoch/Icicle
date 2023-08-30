#Cmake commands take parameters as a list and perform tasks accordingly
#tutorial 1: https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
#tutorial 2: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

#environment variables: https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html

# Have two builds minimum, debug and release

cmake_minimum_required(VERSION 3.9.1)

project(Icicle)

set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code")

# check OS
# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()


if (NOT CMAKE_BUILD_TYPE)
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "None" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" FORCE)
endif ()


# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

#cmake_policy(SET CMP0079 NEW)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/Main/src/*.cpp")
list(APPEND SOURCE_FILES
"${CMAKE_SOURCE_DIR}/Main/src/IcicleMath.cpp"
"${CMAKE_SOURCE_DIR}/Main/src/Allocator.cpp"
"${CMAKE_SOURCE_DIR}/Main/src/StackAllocator.cpp"
"${CMAKE_SOURCE_DIR}/Main/src/MemoryManager.cpp"
)

file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/Main/src/*.h")
list(APPEND HEADER_FILES 
    "${CMAKE_SOURCE_DIR}/Main/Include/IcicleMath.h"
    "${CMAKE_SOURCE_DIR}/Main/Include/Allocator.h"
    "${CMAKE_SOURCE_DIR}/Main/Include/StackAllocator.h"
    "${CMAKE_SOURCE_DIR}/Main/Include/MemoryManager.h"
    "${CMAKE_SOURCE_DIR}/Main/Include/Resource.h"
)






install(FILES ${HEADER_FILES} DESTINATION lib)


add_library(IcicleMain SHARED ${SOURCE_FILES} ${HEADER_FILES} )

target_include_directories(IcicleMain PUBLIC
"${CMAKE_CURRENT_SOURCE_DIR}/Main/Include"
"${CMAKE_BINARY_DIR}/lib")

target_link_directories(IcicleMain PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Main/Include")



add_executable(TestInstantiator Tests/Main/TestInstantiator.cpp )

target_link_libraries(TestInstantiator IcicleMain)
# target_link_libraries(TestInstantiator vtkCommon)


add_test(NAME TestInstantiator
         COMMAND TestInstantiator)

         
         set_source_files_properties(
            $(doctest.h)
            PROPERTIES
            COMPILE_FLAGS " "
        )