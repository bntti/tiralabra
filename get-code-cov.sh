#!/bin/bash

# Remove code coverage for test files
for filename in $(find build-files/tests/obj/tests/ -name "*\.gc*" | egrep "\.(gcda|gcno)"); do
    rm $filename
done

# Get code coverage
for filename in $(find src -name "*\.cpp" | grep -v "main.cpp"); do
    gcov -n -o build-files/tests/obj/src $filename >/dev/null
done
