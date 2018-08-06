CC=g++

make: game.h game.cpp main.cpp
	 $(CC) -o snake main.cpp -lglut -lGLU -lGL -std=c++11
