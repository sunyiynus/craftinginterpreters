Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview5
)

FetchContent_MakeAvailable(Catch2)
#FetchContent_GetProperties(Catch2 Catch2_SOURCE_DIR)
set(SRC_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src)
file(GLOB SRC ./*.cpp)

add_executable(tests ${SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain bello)
message("this is funcing mess ${Catch2_SOURCE_DIR}")
message("this is funcing mess ${SRC_INCLUDE_PATH}")

target_include_directories(tests PRIVATE ${SRC_INCLUDE_PATH})
enable_testing()
target_compile_definitions(tests PUBLIC SOURCE_PATH=${CMAKE_SOURCE_DIR})

message("binary file : ${CMAKE_CURRENT_BINARY_DIR}")
message("binary file : ${CMAKE_BINARY_DIR} ${EXECUTABLE_OUTPUT_PATH}")

add_test (NAME MyTest COMMAND tests -d yes)
add_test (NAME MyTest-1 COMMAND tests)