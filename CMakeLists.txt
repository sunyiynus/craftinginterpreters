cmake_minimum_required(VERSION 3.10)
project(interperter VERSION 0.1.0)

aux_source_directory(src LIB_SRC)
include(CTest)

add_library(bello STATIC ${LIB_SRC})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE bello)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET bello PROPERTY CXX_STANDARD 11)

add_subdirectory(test)