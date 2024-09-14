#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[256]="ABC ";
	strcat(str,"DEF");
	printf("%s\n",str);
	return 0;
}
