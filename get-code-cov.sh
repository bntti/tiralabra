#!/bin/bash

# Remove code coverage for test files.
for filename in `find build-files/tests/obj/tests/ -name "*\.gcda"`;
do
    rm $filename
done
for filename in `find build-files/tests/obj/tests/ -name "*\.gcno"`;
do
    rm $filename
done

# Get code coverage
for filename in `find src -name "*\.cpp" | grep -v "main.cpp"`;
do
    gcov -n -o build-files/tests/obj/src $filename > /dev/null;
done