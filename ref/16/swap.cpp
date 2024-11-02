#include <string>
#include <iostream>

template <class T>
void Swap(T &a,T &b)
{
	auto c=a;
	a=b;
	b=c;
}

int main(void)
{
	std::string x,y;
	x="X";
	y="Y";

	std::cout << "Before " << x << " " << y << "\n";
	Swap<std::string>(x,y);
	std::cout << "After  " << x << " " << y << "\n";

	return 0;
}
