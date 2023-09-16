include_directories(${PROJECT_SOURCE_DIR}/Main/Include)


#TODO: switch this to listing them becuause cmake cannot track dependency changes if use this
file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/Main/src/*.cpp")

add_library(IcicleMain ${SOURCE_FILES})

target_link_libraries(IcicleMain glfw ${GLFW_LIBRARIES} Vulkan::Vulkan glm::glm)