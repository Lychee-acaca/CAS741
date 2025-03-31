#!/bin/bash

# Enter the build directory (make sure the project is built)
SELF_DIR=$(dirname "$(realpath "$0")")
BUILD_DIR=$(realpath "${SELF_DIR}/../build")

# Check if the build directory exists
if [ ! -d "$BUILD_DIR" ]; then
  echo "Build directory does not exist. Please run CMake to build the project first."
  exit 1
fi

# Enter the build directory
cd "$BUILD_DIR"

# Run ctest to execute all tests and keep the original output
echo "Running ctest..."
ctest

# Check if ctest was successful
if [ $? -eq 0 ]; then
  echo "All tests passed!"
else
  echo "Tests failed."
  exit 1
fi
