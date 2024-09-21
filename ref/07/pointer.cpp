#include <iostream>

void Swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
	std::cout << a << " " << *a << "\n";
}

int main(void)
{
	int x=1,y=2;
	std::cout << "Before " << x << " " << y << "\n";
	Swap(&x,&y);
	std::cout << "After  " << x << " " << y << "\n";
	return 0;
}
