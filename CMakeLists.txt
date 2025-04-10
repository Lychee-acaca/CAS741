cmake_minimum_required(VERSION 3.10)
project(RwaveDetection CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

# Configure the build type (Debug/Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Only apply coverage flags for GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    set(COVERAGE_LINK_FLAGS "-fprofile-arcs -ftest-coverage")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${COVERAGE_LINK_FLAGS}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

# Add include directories
include_directories(${PROJECT_SOURCE_DIR})

# Search source files automatically
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# Add executable target (name of executable and source files)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(PROJECT_TEST_NAME "${PROJECT_NAME}_test")

aux_source_directory(${PROJECT_SOURCE_DIR}/test/unitTest TEST_LIST)

add_executable(
  ${PROJECT_TEST_NAME}
  ${TEST_LIST}
  ${PROJECT_SOURCE_DIR}/src/logger.cpp
  ${PROJECT_SOURCE_DIR}/src/mmath.cpp
  ${PROJECT_SOURCE_DIR}/src/generalDigitalFilter.cpp
)

target_link_libraries(
  ${PROJECT_TEST_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST_NAME})
