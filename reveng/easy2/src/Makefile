CC=gcc
CFLAGS=-Wall -Wextra -W -Wpedantic -std=c99

all: easy2.c token.h
	$(CC) $(CFLAGS) easy2.c -o easy2

token.h: gen_token.c
	$(CC) $(CFLAGS) gen_token.c -o gen_token
	./gen_token > token.h

.PHONY: clean
clean:
	rm -fv easy2 gen_token token.h
