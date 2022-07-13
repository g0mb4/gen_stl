CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS = -lm

SRC = $(wildcard *.c)

default:
	$(CC) $(CFLAGS) -o gen_stl $(SRC) $(LDFLAGS)
