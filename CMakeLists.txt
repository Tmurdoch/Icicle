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

#cmake_policy(SET CMP0079 NEW)



file(GLOB HEADER_FILES $(CMAKE_SOURCE_DIR)/Main/src/*.h)
list(APPEND HEADER_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Main/Math/IcicleMath.h"
    "${CMAKE_SOURCE_DIR}/Main/Memory/Allocator.h"
    "${CMAKE_SOURCE_DIR}/Main/Memory/StackAllocator.h"
    "${CMAKE_SOURCE_DIR}/Main/Memory/MemoryManager.h"
    "${CMAKE_SOURCE_DIR}/Main/Resources/Resource.h"
)

file(GLOB SOURCE_FILES $(CMAKE_SOURCE_DIR)/Main/src/*.cpp)
list(APPEND SOURCE_FILES
"${CMAKE_CURRENT_SOURCE_DIR}/Main/Math/IcicleMath.cpp"
"${CMAKE_SOURCE_DIR}/Main/Memory/Allocator.cpp"
"${CMAKE_SOURCE_DIR}/Main/Memory/StackAllocator.cpp"
"${CMAKE_SOURCE_DIR}/Main/Memory/MemoryManager.cpp"
)


add_library(IcicleMain SHARED ${HEADER_FILES} ${SOURCE_FILES})

install(FILES ${HEADER_FILES} DESTINATION include/Icicle)


add_executable(Test "Tests/Main/TestInstantiator.cpp")
target_include_directories(Test PRIVATE 
"${CMAKE_SOURCE_DIR}/Main/src" 
"${CMAKE_SOURCE_DIR}/Main/Math" 
"${CMAKE_SOURCE_DIR}/Main/Memory" 
"${CMAKE_SOURCE_DIR}/Main/Resources")


add_executable(TestInstantiator Tests/Main/TestInstantiator.cpp )
target_link_libraries(TestInstantiator IcicleMain)
# target_link_libraries(TestInstantiator vtkCommon)


add_test(NAME TestInstantiator
         COMMAND TestInstantiator)
