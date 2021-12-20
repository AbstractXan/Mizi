all : test main

flags = -std=c++17 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og

testfiles = test/*.cpp
test:
	g++ ${flags} ${testfiles} test.cpp

files = modules/*.cpp
main:
	g++ ${flags} ${files} main.cpp -o mizi
