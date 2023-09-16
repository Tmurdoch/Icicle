include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(block_test block_test.h block_test.cpp)

target_link_libraries(block_test PRIVATE IcicleMain)