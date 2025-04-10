#!/bin/bash

set -e

cd "$(dirname "$0")/.."

TMPDIR=$(mktemp -d)

lcov -c -i -d . -o "$TMPDIR/base.info"
./test/cTest.sh
lcov -c -d . -o "$TMPDIR/test.info"
lcov -a "$TMPDIR/base.info" -a "$TMPDIR/test.info" -o "$TMPDIR/total.info"
lcov --extract "$TMPDIR/total.info" "$(pwd)/src/*" -o "$TMPDIR/final.info"

rm -rf ./cover_report

genhtml -o ./cover_report --legend --title "lcov" --prefix=./ "$TMPDIR/final.info"

rm -rf "$TMPDIR"

echo "Coverage report generated: $(pwd)/cover_report/"
