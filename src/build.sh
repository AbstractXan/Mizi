#!/bin/bash

rm ../site/*

g++ -std=c++11 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og main.cpp -o main

./main -a
