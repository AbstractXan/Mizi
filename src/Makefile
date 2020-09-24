all : main

main: libs main.o mizi.o
	g++ -o main main.o \
mizi.o category.o config.o \
home.o page.o head.o \
helpers.o linkparser.o

main.o : main.cpp mizi.o
	g++ -c main.cpp
mizi.o : mizi.cpp libs
	g++ -c mizi.cpp
libs : category.o config.o \
home.o page.o head.o helpers.o linkparser.o

category.o : classes/Category/category.cpp page.o 
	g++ -c classes/Category/category.cpp

config.o : classes/Config/config.hpp classes/Config/config.cpp
	g++ -c classes/Config/config.cpp

home.o : classes/Home/home.cpp
	g++ -c classes/Home/home.cpp

page.o : classes/Page/page.cpp classes/Category/category.hpp classes/Home/home.hpp
	g++ -c classes/Page/page.cpp

head.o : classes/Page/head.cpp
	g++ -c classes/Page/head.cpp

helpers.o : helpers/helpers.cpp
	g++ -c helpers/helpers.cpp

linkparser.o : helpers/linkparser.cpp
	g++ -c helpers/linkparser.cpp

clean :
	rm *.o
