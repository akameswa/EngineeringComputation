#include <iostream>
#include <stdlib.h>
#include <time.h>

void GiveSeedToRandomNumberGenerator(void)
{
	srand(time(nullptr));
}

int GenerateARandomNumber(void)
{
	return rand()%10;
}

int PromptTheUserAndTakeInput(void)
{
	int g;
	std::cout << "Guess 0-9:";
	std::cin >> g;
	return g;
}

void CompareAndShowResults(int r,int g)
{
	if(g==r)
	{
		std::cout << "Correct!\n";
	}
	else
	{
		std::cout << "Wrong! Correct answer was:" << r << "\n";
	}
}

int main(void)
{
	GiveSeedToRandomNumberGenerator();
	int r=GenerateARandomNumber();
	int g=PromptTheUserAndTakeInput();
	CompareAndShowResults(r,g);
	return 0;
}
