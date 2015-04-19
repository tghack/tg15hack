#include <stdio.h>
#include <string.h>

char pw[] = "kult_passord\0";
unsigned char enc[15] = { 0 };
char enc_pw[sizeof(pw) + 1] = { 0 };
unsigned char token[] = "kjempeHemmelig";
unsigned char key[] = { 0xa, 0xb, 0xa, 0xd, 0xc, 0xa, 0xf, 0xe };

int main(void)
{
	printf("unsigned char key[] = { ");
	for (int i = 0; i < (int)sizeof(key); i++)
		printf("0x%02x, ", key[i]);
	printf("};\n");

	printf("unsigned char pw[] = { ");
	enc_pw[0] = pw[0] ^ key[0];
	printf("0x%02x, ", enc_pw[0]);
	for (int i = 1; i < (int)strlen(pw); i++) {
		enc_pw[i] = pw[i] ^ key[i % sizeof(key)];
		printf("0x%02x, ", enc_pw[i]);
	}
	printf(" 0x0 };\n");

	printf("unsigned char token[] = { ");
	for (int i = 0; i < (int)sizeof(key); i++)
		printf("0x%02x, ", token[i] ^ key[i]);
	
	int cnt = sizeof(key);
	for (int i = 0; i < (int)(sizeof(token) - sizeof(key)); i++)
		printf("0x%02x, ", token[cnt++] ^ pw[i]);
	printf("};\n");

	return 0;
}
