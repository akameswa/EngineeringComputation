#include <stdio.h>
#include <algorithm>

void BubbleSort(int n,int x[])
{
	for(int i=0; i<n; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			if(x[i]>x[j])
			{
				std::swap(x[i],x[j]);
			}
		}
	}
}

int main(void)
{
	int x[20]={17,10,13,14,15,6,3,2,9,8,18,7,12,11,16,4,1,0,5,19};

	BubbleSort(20,x);

	for(auto a : x)
	{
		printf("%d\n",a);
	}

	return 0;
}
