#!/bin/bash

set -e

cd "$(dirname "$0")/.."

TMPDIR=$(mktemp -d)

lcov -c -i -d . -o "$TMPDIR/base.info"

echo "Collecting coverage data..."

./test/cTest.sh

echo "Test execution completed."

lcov -c -d . -o "$TMPDIR/test.info"
lcov -a "$TMPDIR/base.info" -a "$TMPDIR/test.info" -o "$TMPDIR/total.info"

lcov --extract "$TMPDIR/total.info" "$(pwd)/src/*" -o "$TMPDIR/extract.info"

lcov --remove "$TMPDIR/extract.info" "$(pwd)/src/main.cpp" -o "./final.info"

rm -rf ./cover_report

genhtml -o ./cover_report --legend --title "lcov" --prefix=./ "./final.info"

rm -rf "$TMPDIR"

echo "Coverage report generated: $(pwd)/cover_report/"
