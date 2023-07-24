cmake_minimum_required(VERSION 3.9.1)

project(Icicle_test)

add_executable(out Main/src/main.cpp)

set(CMAKE_CXX_FLAGS "-Wall")

# check OS
# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

#Testing
#see add_test command, CTest***

#https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                    Tests in tests/*.cpp will still be enabled." ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(Doctest.cmake)


#add_test(NAME TestName COMMAND ExecutableToRun arg1 arg2 ...)

add_executable(TestInstantiator Main/TestInstantiator.cpp)
# target_link_libraries(TestInstantiator vtkCommon)
target_link_libraries(TestInstantiator PUBLIC doctest)
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