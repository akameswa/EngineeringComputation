#include <string>
#include <iostream>

int main(void)
{
	std::string line;
	std::cout << "Enter a String:";
	std::getline(std::cin,line);

	std::cout << "You entered:";
	std::cout << line;

	std::cout << "\n";


	int wordCount=0;
	int state=0;
	for(int i=0; 0!=line[i]; ++i)
	{
		if(0==state)
		{
			if(' '!=line[i])
			{
				++wordCount;
				state=1;
			}
		}
		else
		{
			if(' '==line[i])
			{
				state=0;
			}
		}
	}

	std::cout << wordCount << " words.\n";

	return 0;
}
