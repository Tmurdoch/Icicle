#Cmake commands take parameters as a list and perform tasks accordingly
#tutorial 1: https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
#tutorial 2: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

#environment variables: https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Icicle")

option(BUILD_TESTS "Build tests" OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

find_package(Vulkan REQUIRED)

if (WIN32)
message("building for windows")
add_subdirectory(lib/glfw)
SET(GLM_TEST_ENABLE OFF CACHE BOOL "GLM build unit tests")
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
endif (WIN32)

if (UNIX)
message("building for unix")
find_package(glfw3 REQUIRED)
SET(GLM_TEST_ENABLE OFF CACHE BOOL "GLM build unit tests")
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
endif (UNIX)

# Include sub-projects.
add_subdirectory ("Main")

if (BUILD_TESTS)
	add_subdirectory ("Tests")
	enable_testing()
endif()