include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(editor editor.cpp "stb/stb_image.h" "stb/stb_image_resize.h" "stb/stb_image_write.h")

target_link_libraries(editor PRIVATE IcicleMain)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/Tests/editor/shaders/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures/ DESTINATION ${CMAKE_BINARY_DIR}/Tests/editor/textures/)