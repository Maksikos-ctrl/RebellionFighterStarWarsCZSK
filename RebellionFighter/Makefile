export LD_PRELOAD=$(shell find /usr -name libasan.so)

# set the compiler
CC = gcc

# set the compiler flags
CFLAGS := $(shell sdl2-config --libs --cflags) -ggdb3 -O0 --std=c99 -Wall -fsanitize=address -static-libasan -g
LDFLAGS := $(shell sdl2-config --static-libs) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -Wl,--no-as-needed,-rpath=.


HDRS :=

SRCS := main.c bullets.c

OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := intro

all: $(EXEC)

# recipe for building the executable
$(EXEC): $(OBJS)
	LD_PRELOAD=$$(echo '#include <unistd.h>\n __attribute__((constructor)) void preload() { setenv("LD_PRELOAD", "libasan.so", 1); }' | $(CC) -x c - -fPIC -shared -ldl -o preload.so)


# recipe for building main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# recipe for building bullets.o
bullets.o: bullets.c bullets.h
	$(CC) $(CFLAGS) -c bullets.c 









