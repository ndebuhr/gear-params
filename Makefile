CC=gcc
FLAGS=-g

all: gear_params
	./gear_params

gear_params: gear_params.o get_teeth.o
	$(CC) -g -o gear_params gear_params.o get_teeth.o

gear_params.o: gear_params.c
	$(CC) -g -c -o gear_params.o gear_params.c

get_teeth.o: get_teeth.c
	$(CC) -g -c -o get_teeth.o get_teeth.c

clean:
	rm gear_params gear_params.o get_teeth.o
