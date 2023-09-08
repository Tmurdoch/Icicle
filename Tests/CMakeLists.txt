include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(TestInt TestInstantiator.cpp)

#target_link_libraries(Test IcicleMain)

#setup testing framework ------ https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#top

# enable FetchContent
include(FetchContent)

FetchContent_Declare(Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2
GIT_TAG		   v3.0.1
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(TestInt PRIVATE IcicleMain Catch2::Catch2)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(TestInt)

enable_testing()

add_test(
	NAME IceTest
	COMMAND $<TARGET_FILE:TestInt> --sucess
)