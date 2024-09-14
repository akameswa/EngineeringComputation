#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char str[256];
	printf("Enter a String:");
	fgets(str,255,stdin);

	printf("You Entered: %s",str);

	int i=0;
	for(i=0; i<strlen(str); ++i) // <-> Same but -> is faster for(i=0; 0!=str[i]; ++i)
	{
		if(0==isprint(str[i])) // pretty much the same <->if(str[i]<' ')
		{
			str[i]=0;
			break;
		}
	}
	printf("%d letters\n",i);

	for(i=0; 0!=str[i]; ++i)
	{
		printf("%d\n",str[i]);
	}

	return 0;
}
