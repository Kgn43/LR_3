#!/bin/bash

cd boostTest/
mkdir files

g++ -g -O0 --coverage -o files/testsArr arrayTESTS.cpp classes/arr.cpp

./files/testsArr

g++ -g -O0 --coverage -o files/testsHashMap hashMapTESTS.cpp classes/arr.cpp classes/list.cpp classes/Pair.cpp classes/hashMap.cpp

./files/testsHashMap

g++ -g -O0 --coverage -o files/testsList listTESTS.cpp classes/list.cpp classes/Pair.cpp

./files/testsList

g++ -g -O0 --coverage -o files/testsQueue queueTESTS.cpp classes/queue.cpp

./files/testsQueue

g++ -g -O0 --coverage -o files/testsSCL sclTESTS.cpp classes/singleConnList.cpp

./files/testsSCL

g++ -g -O0 --coverage -o files/testsStack stackTESTS.cpp classes/Stack.cpp

./files/testsStack

lcov --capture --directory ./files --output-file coverage.info --rc geninfo_unexecuted_blocks=1 --ignore-errors inconsistent

genhtml coverage.info --output-directory coverage_html

xdg-open coverage_html/index.html
