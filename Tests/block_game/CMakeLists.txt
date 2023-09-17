include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(block_test_game block_test.cpp)

target_link_libraries(block_test_game PRIVATE IcicleMain)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/Tests/block_game)