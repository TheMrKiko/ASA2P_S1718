#!/bin/bash  

g++ -std=c++11 -O3 -Wall -o proj main.cpp -lm

for arg in "$@"
do
	echo ""
  	echo "Running $arg"
  	time ./proj < "${arg%.*}".in > "${arg%.*}".out.bla
  	diff -q "${arg%.*}".out "${arg%.*}".out.bla
done

rm *.bla
rm bla
