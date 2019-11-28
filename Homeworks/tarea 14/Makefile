
FLAGS=-Wall -g
CC=g++

build:
	${CC} ${FLAGS} pgm.cpp draw.cpp point.cpp convex_hull.cpp main.cpp -o main $(shell pkg-config --cflags --libs cairo)
