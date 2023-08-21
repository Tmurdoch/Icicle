#Cmake commands take parameters as a list and perform tasks accordingly
#tutorial 1: https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
#tutorial 2: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

#environment variables: https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html

# Have two builds minimum, debug and release

cmake_minimum_required(VERSION 3.9.1)

project(Icicle)

set(CMAKE_CXX_FLAGS "-Wall")

# check OS
# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()


#use this when adding packages as source to project, this is where cmakes search path is
#set(CMAKE_MODULE_PATH) {
#    $(PROJECT_SOURCE_DIR)
#}

if (NOT CMAKE_BUILD_TYPE)
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "None" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" FORCE)
endif ()


# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")


# TODO: 

# what artifacts should the library produce at install step
# where install artifacts should be placed
# how other applications can find the library
# when they are using it pre-built as an external dependency
# when its sources are nested in their source tree
# will it be static or shared library
# will you need to have it as DLL on Windows



add_subdirectory(Main/Math)
add_subdirectory(Main/Memory)
add_subdirectory(Main/src)



add_executable(TestInstantiator Tests/Main/TestInstantiator.cpp )

# target_link_libraries(TestInstantiator vtkCommon)
target_link_libraries(TestInstantiator PUBLIC doctest LibMemory Math)
cmake_policy(SET CMP0079 NEW)
target_link_libraries(LibMemory PUBLIC Math)
add_test(NAME TestInstantiator
         COMMAND TestInstantiator)



#To run build test directory make /build directory then run:
#cmake .. -G"MSYS Makefiles" -B .
#if on windows

# set_property(TEST test_name
#              PROPERTY prop1 value1 value2 ...)

# TODO: 
# create the testing file and list of tests
# create_test_sourcelist (Tests
#   CommonCxxTests.cxx
#   ObjectFactory.cxx
#   otherArrays.cxx
#   otherEmptyCell.cxx
#   TestSmartPointer.cxx
#   SystemInformation.cxx
#   ...
#   )

# # add the executable
# add_executable (CommonCxxTests ${Tests})

# # remove the test driver source file
# set (TestsToRun ${Tests})
# remove (TestsToRun CommonCxxTests.cxx)

# # Add all the ADD_TEST for each test
# foreach (test ${TestsToRun})
#   get_filename_component (TName ${test} NAME_WE)
#   add_test (NAME ${TName} COMMAND CommonCxxTests ${TName})
# endforeach ()

#TODO: test build
# add_test(
#   NAME
#     ExampleCMakeBuild
#   COMMAND
#     "${CMAKE_CTEST_COMMAND}"
#              --build-and-test "${My_SOURCE_DIR}/examples/simple"
#                               "${CMAKE_CURRENT_BINARY_DIR}/simple"
#              --build-generator "${CMAKE_GENERATOR}"
#              --test-command "${CMAKE_CTEST_COMMAND}"
# )