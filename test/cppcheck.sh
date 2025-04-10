#!/bin/bash

SELF_DIR=$(dirname "$(realpath "$0")")
SOURCE_DIR=$(realpath "${SELF_DIR}/../src")
TEST_DIR=$(realpath "${SELF_DIR}/unitTest")

run_cppcheck() {
    local target_dir="$1"
    local output

    echo "Running cppcheck on $target_dir"
    output=$(cppcheck --enable=all --inconclusive --quiet --suppress=missingInclude "$target_dir" 2>&1)
    local status=$?

    if [[ -n "$output" ]]; then
        echo "Cppcheck analysis on $target_dir found issues:"
        echo "$output"
        exit 1
    elif [[ $status -ne 0 ]]; then
        echo "Cppcheck encountered an error while analyzing $target_dir."
        exit 1
    else
        echo "Cppcheck analysis on $target_dir completed successfully."
    fi
}

run_cppcheck "$SOURCE_DIR"
run_cppcheck "$TEST_DIR"
