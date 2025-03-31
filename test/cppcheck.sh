#!/bin/bash

PROJECT_DIR=$(dirname "$(realpath "$0")")
SOURCE_DIR=$(realpath "${PROJECT_DIR}/../src")

if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory $SOURCE_DIR does not exist."
    exit 1
fi

echo "Running cppcheck on $SOURCE_DIR"
cppcheck --enable=all --inconclusive --check-config --quiet --suppress=missingInclude "$SOURCE_DIR"

if [ $? -eq 0 ]; then
    echo "Cppcheck analysis completed successfully."
else
    echo "Cppcheck analysis found issues."
    exit 1
fi
