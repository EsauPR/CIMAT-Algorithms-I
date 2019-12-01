FLAGS=-Wall -g
CC=g++

build:
	${CC} ${FLAGS} canvas.cpp chess.cpp main.cpp -o main $(shell pkg-config --cflags --libs cairo gtkmm-3.0)
