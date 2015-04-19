/*
 * easy1
 * Solutions: strings, ltrace, looking at the asm, etc.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

const char *super_secret_password = "secret\n";
const char *token = "F62wAk-aY3<PCoF";

int main(void)
{
	char buf[15] = { 0 };

	fprintf(stderr, "Enter the secret password: ");
	read(STDIN_FILENO, buf, sizeof(buf) - 1);

	if (!strcmp(buf, super_secret_password))
		printf("Correct! The token is: %s\n", token);
	else
		printf("Wrong :(\n");

	return 0;
}
