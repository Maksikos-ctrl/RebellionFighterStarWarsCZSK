CC = gcc
CFLAGS = -Wall -I/usr/include
LDFLAGS = -L/usr/lib -lGL -lGLU -lglut -lm


OBJECTS = main.o drawPlayer.o drawEnemies.o



all: main

main: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c draw.h
	$(CC) $(CFLAGS) -c main.c	

drawPlayer.o: drawPlayer.c draw.h
	$(CC) $(CFLAGS) -c drawPlayer.c

drawEnemies.o: drawEnemies.c draw.h
	$(CC) $(CFLAGS) -c drawEnemies.c

clean:
	rm -f main main.o drawPlayer.o drawEnemies.o
