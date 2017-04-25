CC=gcc

all: get_teeth

get_teeth: get_teeth.c
	$(CC) get_teeth.c -o get_teeth

clean:
	rm get_teeth
