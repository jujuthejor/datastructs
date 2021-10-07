CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -pedantic
TARGET=datastructs

ifeq ($(OS), Windows_NT)
	RM=del /Q /S
else
	RM=rm -r
endif

SRCS=$(wildcard *.c)
BINS=$(SRCS:.c=.o)

TESTS=$(basename $(wildcard *_test.c))

.PHONY: all test clean

all: $(BINS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

test: $(TESTS)

hashtable_test: hashtable_test.o hashtable.o list.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(BINS) $(TARGET)*
