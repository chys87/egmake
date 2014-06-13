#!/bin/bash

if [[ ! -r "$1" ]]; then
	echo "You must specify a filename." >&2
	exit 1
fi

TEST_TARGET="test-${1##*/}"
TEST_TARGET="${TEST_TARGET%.*}"

echo "load egmake.so"
echo ".PHONY: $TEST_TARGET"
echo ".DEFAULT_GOAL = $TEST_TARGET"
echo ".SUFFIXES :="

sed -n -e '
/MAKEFILE-TEST-BEGIN/,/MAKEFILE-TEST-END/ { /MAKEFILE-TEST-\(BEGIN\|END\)/d; p }
' $1
