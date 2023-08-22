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


if (NOT CMAKE_BUILD_TYPE)
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "None" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" FORCE)
endif ()


# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

cmake_policy(SET CMP0079 NEW)

add_executable(TestInstantiator Tests/Main/TestInstantiator.cpp )

target_include_directories(TestInstantiator PRIVATE "Tests" "Main/src" "Main/Math" "Main/Memory")

add_subdirectory(Main/src)
add_subdirectory(Main/Math)
add_subdirectory(Main/Memory)
#add_subdirectory(Main/Resources)






# target_link_libraries(TestInstantiator vtkCommon)
target_link_libraries(LibMemory PUBLIC Math)
target_link_libraries(TestInstantiator PUBLIC LibMath LibMemory)

add_test(NAME TestInstantiator
         COMMAND TestInstantiator)

message($(SOURCE_FILES))