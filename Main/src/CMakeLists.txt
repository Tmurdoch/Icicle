include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/Main/src/*.cpp")

add_library(IcicleMain ${SOURCE_FILES})