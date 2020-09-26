all : test main

flags = -std=c++11 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og

testfiles = test/*.cpp
test:
	g++ ${flags} ${testfiles} test.cpp

files = classes/*.cpp
main:
	g++ ${flags} ${files} main.cpp -o main
