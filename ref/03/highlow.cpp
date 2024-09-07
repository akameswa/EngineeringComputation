#include <iostream>
#include <stdlib.h>
#include <time.h>



int main(void)
{
	srand((unsigned int)(time(nullptr)));

	int r=rand()%10,g;

	for(;;)
	{
		std::cout << "Guess 0-9:";
		std::cin >> g;

		if(r==g)
		{
			std::cout << "You win!" << "\n";
			break;
		}
		else if(g<r)
		{
			std::cout << "Too low. Try agian.\n";
		}
		else // if(g>r)
		{
			std::cout << "Too high. Try agian.\n";
		}
	}

	return 0;
}
