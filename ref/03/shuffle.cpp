#include <iostream>
#include <stdlib.h>
#include <time.h>



void Swap(int &a,int &b)
{
	auto c=a;
	a=b;
	b=c;
}

void MakeNonRepeatingRandomNumber(int N,int r[])
{
	for(int i=0; i<N; ++i)
	{
		r[i]=i;
	}

	for(int i=0; i<N; ++i)
	{
		auto j=rand()%N;
		Swap(r[i],r[j]);  // As good as std::swap(r[i],r[j]); #include <algorithm>
	}
}

int main(void)
{
	srand(time(nullptr));

	int r[20];
	MakeNonRepeatingRandomNumber(20,r);

	for(auto x : r)
	{
		std::cout << x << "\n";
	}

	return 0;
}
