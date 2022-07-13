CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS = -lm

SRC = box.c\
	  cylinder.c\
	  pipe.c\
      error.c\
	  facet.c\
	  gen_stl.c

default:
	$(CC) $(CFLAGS) -o gen_stl $(SRC) $(LDFLAGS)
