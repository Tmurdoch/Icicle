include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(testinstantiator TestInstantiator.cpp "tickleSim/tickleSim.cpp")


#target_link_libraries(Test IcicleMain)

#setup testing framework ------ https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#top

# enable FetchContent
include(FetchContent)

FetchContent_Declare(Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2
GIT_TAG		   v3.3.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(testinstantiator PRIVATE Icicle Catch2::Catch2WithMain)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
include(CTest)
catch_discover_tests(testinstantiator)

option(BUILD_EDITOR "Build editor" OFF)
if (BUILD_EDITOR)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/editor/")
endif()

#add_test(
#	NAME IceTest
#	COMMAND $<TARGET_FILE:testinstantiator> --success
#)
