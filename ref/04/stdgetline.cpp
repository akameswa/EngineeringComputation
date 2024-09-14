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

	return 0;
}
