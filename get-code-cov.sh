#!/bin/bash
for filename in `find tests -name "*\.cpp"`; 
do 
  gcov -n -o build-files/tests/obj/tests $filename > /dev/null; 
done

for filename in `find src -name "*\.cpp" | grep -v "main.cpp"`; 
do 
  gcov -n -o build-files/tests/obj/src $filename > /dev/null; 
done