CC=gcc
FLAGS=-g

all: gear_params
	./gear_params

gear_params: gear_params.c
	$(CC) -g -o gear_params gear_params.c

clean:
	rm gear_params
