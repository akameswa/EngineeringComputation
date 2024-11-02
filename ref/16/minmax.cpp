#include <iostream>
#include <algorithm>

template <class T>
T smaller(T a,T b)
{
	if(a<b)
	{
		return a;
	}
	return b;
}

int main(void)
{
	int a=100;
	unsigned int b=200;
	std::cout << std::min<unsigned>(a,b) << std::endl;
	return 0;
}
