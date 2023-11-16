include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(editor editor.cpp)

target_link_libraries(editor PRIVATE Icicle)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/Tests/editor/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures/ DESTINATION ${CMAKE_BINARY_DIR}/Tests/editor/)