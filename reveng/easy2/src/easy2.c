/*
 * easy2
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "token.h"

#define KEY 0x3
#define ENC(x) (char)(((int)(x)) ^ KEY)
char pw[] = { ENC('T'), ENC('G'), ENC('1'), ENC('5'), '\0' };

static inline void print_token(void)
{
	for (int i = 0; token[i]; i++)
		putchar(token[i] ^ KEY);
}

int main(void)
{
	char buf[50] = { 0 };
	char cmp[sizeof(pw)] = { 0 };
	ssize_t ret;

	fprintf(stderr, "Password: ");
	ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	buf[ret - 1] = '\0';

	for (int i = 0; i < (int)sizeof(pw) - 1; i++)
		cmp[i] = pw[i] ^ KEY;

	if (!strcmp(buf, cmp)) {
		printf("Correct! The token is: ");
		print_token();
	} else {
		printf("Wrong password!");
	}

	printf("\n");

	return 0;
}
