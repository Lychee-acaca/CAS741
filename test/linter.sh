#!/bin/bash

SELF_DIR=$(dirname "$(realpath "$0")")
SOURCE_DIR=$(realpath "${SELF_DIR}/../src")
TEST_DIR=$(realpath "${SELF_DIR}/unitTest")

find "$SOURCE_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \) | while read file; do
    echo "Checking $file"
    cpplint "$file"
done

find "$TEST_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \) | while read file; do
    echo "Checking $file"
    cpplint "$file"
done
