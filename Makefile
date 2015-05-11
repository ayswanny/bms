.Phony: all test

all:
	gcc -std=c99 -g buddy_system.c gui.c -o bms `pkg-config --cflags --libs gtk+-3.0`

test: 
	gcc -std=c99 -g -Wall buddy_system.c test.c -o test
	