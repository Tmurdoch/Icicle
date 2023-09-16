include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(testinstantiator TestInstantiator.cpp)


#target_link_libraries(Test IcicleMain)

#setup testing framework ------ https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#top

# enable FetchContent
include(FetchContent)

FetchContent_Declare(Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2
GIT_TAG		   v3.0.1
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(testinstantiator PRIVATE IcicleMain Catch2::Catch2WithMain)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
include(CTest)
catch_discover_tests(testinstantiator)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/block_game/")

#add_test(
#	NAME IceTest
#	COMMAND $<TARGET_FILE:testinstantiator> --success
#)