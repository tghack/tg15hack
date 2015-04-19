CC=gcc
CFLAGS=-Wall -Wextra -W -Wpedantic -std=gnu99 -O3

all: srv.c
	$(CC) $(CFLAGS) $< -o srv

.PHONY: clean
clean:
	rm -v srv
