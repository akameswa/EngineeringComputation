#include <string>
#include <iostream>
#include <vector>


std::vector <std::string> ParseString(std::string input)
{
	int state=0;
	std::vector <std::string> args;
	for(auto c : input)
	{
		if(0==state)
		{
			if(' '!=c && '\t'!=c)
			{
				std::string str;
				str.push_back(c);
				args.push_back(str);
				state=1;
			}
		}
		else
		{
			if(' '==c || '\t'==c)
			{
				state=0;
			}
			else
			{
				args.back().push_back(c);
			}
		}
	}
	return args;
}

int main(void)
{
	std::cout << "Enter text>";

	std::string str;
	std::getline(std::cin,str);

	auto args=ParseString(str);
	for(auto a : args)
	{
		std::cout << a << "\n";
	}

	return 0;
}
