#!/bin/bash

PROJECT_DIR=$(dirname "$(realpath "$0")")/..
SOURCE_DIR=${PROJECT_DIR}/src

if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory $SOURCE_DIR does not exist."
    exit 1
fi

find "$SOURCE_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \) | while read file; do
    echo "Checking $file"
    cpplint "$file"
done
