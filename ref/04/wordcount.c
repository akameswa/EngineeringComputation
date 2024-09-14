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


	int wordCount=0;
	int state=0;
	for(int i=0; 0!=str[i]; ++i)
	{
		if(0==state)
		{
			if(' '!=str[i])
			{
				++wordCount;
				state=1;
			}
		}
		else
		{
			if(' '==str[i])
			{
				state=0;
			}
		}
	}

	printf("%d words.\n",wordCount);

	return 0;
}
