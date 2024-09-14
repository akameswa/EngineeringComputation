#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[256];

	strcpy(str,"ABCDEFG");
	printf("%s\n",str+3);

	return 0;
}
