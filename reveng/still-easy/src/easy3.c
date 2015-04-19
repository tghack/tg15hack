/*
 * A little harder than the second one.
 * The token is XOR encrypted with both the key and the password.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include "pw.h"

/*
 * For every hex value in a hex encoded string, xor with another value.
 */
static inline unsigned char *xor_encrypt(const char *str, unsigned char key[8])
{
	int len = strlen(str);
	int pos = 0;
	unsigned char *buf = calloc(1, strlen(str) + 1);

	for (int i = 0; i < len; i++) {
		if (pos == 8)
			pos = 0;
		buf[i] = str[i] ^ key[pos++];
	}

	return buf;
}

static inline int _strcmp(unsigned const char *s, unsigned const char *t)
{
	char c1, c2;

	do {
		c1 = *s++;
		c2 = *t++;
		if (c1 == '\0')
			return c1 - c2;
	} while (c1 == c2);

	return c1 - c2;
}

static inline void print_token(char *str)
{
	for (int i = 0; i < (int)sizeof(key); i++)
		putchar(token[i] ^ key[i]);

	int cnt = sizeof(key);
	int lim = strlen(str) > sizeof(token) - sizeof(key) ?
			sizeof(token) - sizeof(key) : strlen(str);
	for (int i = 0; i < lim; i++)
		putchar(token[cnt++] ^ str[i]);
}

#if 1
static inline void __attribute__((constructor)) dritt(void)
{
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		printf("no trace pls :(\n");
		exit(EXIT_FAILURE);
	}
}
#endif

int main(void)
{
	ssize_t ret;
	unsigned char *enc;
	char buf[50] = { 0 };

	fprintf(stderr, "Password: ");
	ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	buf[ret - 1] = '\0';

	enc = xor_encrypt(buf, key);

	if (!_strcmp(enc, pw)) {
		printf("Correct! Token is: ");
		print_token(buf);
	} else {
		printf("Wrong password!");
	}

	printf("\n");

	return 0;
}
