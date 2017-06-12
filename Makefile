CC=gcc
FLAGS=-g

all: gear_params.o spur_gears.o rack_pinion.o metric_US.o
	$(CC) -g -o gear_params gear_params.o spur_gears.o rack_pinion.o metric_US.o

gear_params.o: gear_params.c
	$(CC) -g -c -o gear_params.o gear_params.c

spur_gears.o: spur_gears.c
	$(CC) -g -c -o spur_gears.o spur_gears.c

rack_pinion.o: rack_pinion.c
	$(CC) -g -c -o rack_pinion.o rack_pinion.c

metric_US.o: metric_US.c
	$(CC) -g -c -o metric_US.o metric_US.c

clean:
	rm gear_params gear_params.o spur_gears.o rack_pinion.o metric_US.o
