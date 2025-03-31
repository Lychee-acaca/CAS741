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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

# Add include directories
include_directories(${PROJECT_SOURCE_DIR})

# Search source files automatically
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# Add executable target (name of executable and source files)
add_executable(${PROJECT_NAME} ${SRC_LIST})
