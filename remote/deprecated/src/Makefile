CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wno-deprecated-declarations -fno-stack-protector -std=c89

all: gets.c
	$(CC) $(CFLAGS) -o gets $< 2>/dev/null
	execstack -s gets
	sudo chown flag:flag gets
	sudo chmod a+s gets

shell: shell.s
	nasm -felf64 shell.s -o shell.o
	ld shell.o -o shell

.PHONY: clean
clean:
	rm -v gets
