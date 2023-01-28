# A simple makefile for the SDL intro project

# set the compiler
CC = gcc


# set the compiler flags
CFLAGS := $(shell sdl2-config --libs --cflags) -ggdb3 -O0 --std=c99 -Wall 
LDFLAGS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


# add header files here
HDRS :=

# add source files here
SRCS := main.c

# generate names of object files
OBJS := $(SRCS:.c=.o)




# name of executable
EXEC := intro




# default recipe
all: $(EXEC)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXEC)



# name of executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXEC)



main.o: main.c
	$(CC) $(LDFLAGS) -c main.c



