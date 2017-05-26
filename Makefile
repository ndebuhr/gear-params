CC=gcc
FLAGS=-g

all: gear_params.o get_teeth.o rack_pinion.o worm_gear.o
	$(CC) -g -o gear_params gear_params.o get_teeth.o rack_pinion.o worm_gear.o

gear_params.o: gear_params.c
	$(CC) -g -c -o gear_params.o gear_params.c

get_teeth.o: get_teeth.c
	$(CC) -g -c -o get_teeth.o get_teeth.c

rack_pinion.o: rack_pinion.c
	$(CC) -g -c -o rack_pinion.o rack_pinion.c

worm_gear.o: worm_gear.c
	$(CC) -g -c -o worm_gear.o worm_gear.c

clean:
	rm gear_params gear_params.o get_teeth.o rack_pinion.o worm_gear.o
