#!/bin/bash

SELF_DIR=$(dirname "$(realpath "$0")")
SOURCE_DIR=$(realpath "${SELF_DIR}/../src")
TEST_DIR=$(realpath "${SELF_DIR}/unitTest")

echo "Running cppcheck on $SOURCE_DIR"
cppcheck --enable=all --inconclusive --check-config --quiet --suppress=missingInclude "$SOURCE_DIR"

if [ $? -eq 0 ]; then
    echo "Cppcheck analysis on $SOURCE_DIR completed successfully."
else
    echo "Cppcheck analysis on $SOURCE_DIR found issues."
    exit 1
fi

echo "Running cppcheck on $TEST_DIR"
cppcheck --enable=all --inconclusive --check-config --quiet --suppress=missingInclude "$TEST_DIR"

if [ $? -eq 0 ]; then
    echo "Cppcheck analysis on $TEST_DIR completed successfully."
else
    echo "Cppcheck analysis on $TEST_DIR found issues."
    exit 1
fi
