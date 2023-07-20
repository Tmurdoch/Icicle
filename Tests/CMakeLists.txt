cmake_minimum_required(VERSION 3.9.1)

project(Icicle)

add_executable(out Main/src/main.cpp)

set(CMAKE_CXX_FLAGS "-Wall")

# check OS
# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()

#Testing
#see add_test command, CTest***