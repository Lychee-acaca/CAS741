#!/bin/bash

SELF_DIR=$(dirname "$(realpath "$0")")
SOURCE_DIR=$(realpath "${SELF_DIR}/../src")
TEST_DIR=$(realpath "${SELF_DIR}/unitTest")

EXIT_CODE=0  # Initialize exit code

# Function to run cpplint and check for errors in the output
run_cpplint() {
    local file="$1"
    output=$(cpplint "$file")  # Capture cpplint output
    echo "$output"  # Print the output
    if echo "$output" | grep -q "Total errors found:"; then
        echo "cpplint found errors in $file! Exiting with status 1."
        EXIT_CODE=1  # Update the exit code if errors are found
    fi
}

# Check source code files
for file in $(find "$SOURCE_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \)); do
    echo "Checking $file"
    run_cpplint "$file"  # Run cpplint check
    # If errors are found, exit immediately
    if [[ $EXIT_CODE -eq 1 ]]; then
        exit 1  # Exit the script if an error was found
    fi
done

# Check test files
for file in $(find "$TEST_DIR" -type f \( -name "*.cpp" -o -name "*.hpp" \)); do
    echo "Checking $file"
    run_cpplint "$file"  # Run cpplint check
    # If errors are found, exit immediately
    if [[ $EXIT_CODE -eq 1 ]]; then
        exit 1  # Exit the script if an error was found
    fi
done

# If no errors were found, continue
echo "All files passed cpplint checks!"
exit 0  # Exit successfully if no errors found
