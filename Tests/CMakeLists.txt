include_directories(${PROJECT_SOURCE_DIR}/Main/Include)

add_executable(Test TestInstantiator.cpp)

target_link_libraries(Test IcicleMain)

enable_testing()