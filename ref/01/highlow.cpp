#include <iostream>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand(time(nullptr));

	int r=rand()%10;
	int g;

	std::cout << "Guess 0-9:";
	std::cin >> g;

	if(g==r)
	{
		std::cout << "Correct!\n";
	}
	else
	{
		std::cout << "Wrong! Correct answer was:" << r << "\n";
	}
	return 0;
}
