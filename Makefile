CC=gcc
FLAGS=-g

all: get_teeth

get_teeth: get_teeth.c
	$(CC) -g -o get_teeth get_teeth.c

clean:
	rm get_teeth
