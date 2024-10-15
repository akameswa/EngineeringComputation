#include <stdio.h>

int main(void)
{
	short x=0,maxx=0;
	for(;;)  // How can we do it without the knowledge that x will underflow to a negative number?
	{
		++x;

		if(maxx<x)
		{
			maxx=x;
		}
		else
		{
			break;
		}
	}
	printf("%d\n",maxx);
	return 0;
}
