#!/bin/sh
g++ --std=c++11 -Wall -O2 -o ai.out ai.cpp || exit 1
g++ --std=c++11 -Wall -O2 -o reactive.out reactive.cpp || exit 1
./reactive.out ./ai.out
