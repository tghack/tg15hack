#include <stdio.h>

int main(void)
{
	char buf[64];

#if 1
	printf("%p\n", buf);
#endif

	gets(buf);

	printf("You entered: %s\n", buf);

	return 0;
}
