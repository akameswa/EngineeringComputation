#include <stdio.h>

int main(void)
{
	FILE *fp=fopen("readfile.cpp","r");
	if(nullptr!=fp)
	{
		char str[256];
		while(nullptr!=fgets(str,255,fp))
		{
			printf("%s\n",str);
		}
		fclose(fp);
	}
	return 0;
}
