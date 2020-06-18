#!/bin/bash

rm ../site/*

g++ -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og main.cpp -o main

./main -a
