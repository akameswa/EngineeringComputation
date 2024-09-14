#include <stdio.h>
#include <algorithm>

void PrintGraph(int n,int x[])
{
	for(int i=0; i<n; ++i)
	{
		printf("[%2d]",i);
		for(int j=0; j<x[i]; ++j)
		{
			printf("*");
		}
		printf("\n");
	}
}

void BubbleSort(int n,int x[])
{
	for(int i=0; i<n; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			if(x[i]>x[j])
			{
				std::swap(x[i],x[j]);

				PrintGraph(n,x);
				printf(">");
				getchar();
			}
		}
	}
}

int main(void)
{
	int x[20]={17,10,13,14,15,6,3,2,9,8,18,7,12,11,16,4,1,0,5,19};

	PrintGraph(20,x);
	printf("--------\n");

	BubbleSort(20,x);

	for(auto a : x)
	{
		printf("%d\n",a);
	}

	BubbleSort(20,x);

	return 0;
}
