#include <iostream>
#include <stdlib.h>
#include <time.h>



void Swap(int &a,int &b)
{
	auto c=a;
	a=b;
	b=c;
}

int main(void)
{
	srand(time(nullptr));

	int r[20];
	for(int i=0; i<20; ++i)
	{
		r[i]=i;
	}

	for(auto &x : r)
	{
		auto j=rand()%20;
		Swap(x,r[j]);  // As good as std::swap(r[i],r[j]); #include <algorithm>
	}

	for(auto x : r)
	{
		std::cout << x << "\n";
	}

	return 0;
}
