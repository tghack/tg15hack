#include <stdio.h>
#define KEY 0x3

const char token[] = "4iqvMHSH(0";

int main(void)
{
	printf("const char token[] = { ");

	for (int i = 0; i < (int)sizeof(token); i++)
		printf("0x%02x, ", token[i] ^ KEY); 

	printf(" 0 };\n");

	return 0;
}
