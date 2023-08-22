# define header and source files for the library
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(LibResources ${ICICLE_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})