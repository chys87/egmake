#!/bin/bash

if [[ ! -r "$1" ]]; then
	echo "You must specify a filename." >&2
	exit 1
fi

echo "load egmake.so"
echo ".PHONY: test"
echo "test:"
echo ".SUFFIXES :="

sed -n -e '
/MAKEFILE-TEST-BEGIN/,/MAKEFILE-TEST-END/ { /MAKEFILE-TEST-\(BEGIN\|END\)/d; p }
' $1
