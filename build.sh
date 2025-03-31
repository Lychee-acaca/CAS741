#!/bin/bash

# Define the build directory and the build type (Release or Debug)
BUILD_DIR="build"
BUILD_TYPE="Debug"  # Change to "Release" for Release build

# Check if the user passed a build type argument
if [ ! -z "$1" ]; then
  BUILD_TYPE=$1
fi

# Create the build directory if it doesn't exist
mkdir -p ${BUILD_DIR}

# Navigate to the build directory
cd ${BUILD_DIR}

# Run cmake to configure the project and specify Ninja as the generator
echo "Configuring the project with CMake (Build Type: ${BUILD_TYPE})..."
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G Ninja ..

# Check if CMake configuration was successful
if [ $? -ne 0 ]; then
  echo "CMake configuration failed!"
  exit 1
fi

# Build the project using Ninja
echo "Building the project using Ninja..."
ninja

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build completed successfully!"
else
  echo "Build failed!"
  exit 1
fi
