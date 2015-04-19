CC=gcc
CFLAGS=-Wall -Wextra -W -Wpedantic -std=c99

all: easy3

easy3: pw.h
	$(CC) $(CFLAGS) easy3.c -o easy3

pw.h: gen_pw.c
	$(CC) $(CFLAGS) gen_pw.c -o gen_pw
	./gen_pw > pw.h

.PHONY: clean
clean:
	rm -v easy3 gen_pw pw.h
