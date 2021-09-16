CC=gcc
CFLAGS=-g -Og -Wall -Wextra -Werror -std=c99 -pedantic
TARGET=datastructs

ifeq ($(OS), Windows_NT)
	RM=del /Q /S
else
	RM=rm -r
endif

SRCS=$(wildcard *.c)
BINS=$(SRCS:.c=.o)

.PHONY: all clean

all: $(BINS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(BINS) $(TARGET)*
