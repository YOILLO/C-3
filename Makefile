
all: program

program: main.cpp number.cpp
	g++ main.cpp number.cpp -o program
