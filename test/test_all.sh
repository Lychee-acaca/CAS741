#!/bin/bash

SELF_DIR=$(dirname "$(realpath "$0")")

bash "$SELF_DIR/linter.sh" || exit 1

bash "$SELF_DIR/cppcheck.sh" || exit 1

# bash "$SELF_DIR/cTest.sh" || exit 1

bash "$SELF_DIR/lcovTest.sh" || exit 1

echo "All tests executed successfully!"
exit 0
