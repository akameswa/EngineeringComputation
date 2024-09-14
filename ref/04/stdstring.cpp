#include <string>
#include <iostream>

int main(void)
{
	std::string s;

	s="24780";
	s=s+" Engineering";
	s+=" Computation";
	s.push_back('\n');

	std::cout << s;

	for(auto c : s)
	{
		std::cout << c << "\n";
	}

	for(int i=0; i<s.size(); ++i)
	{
		std::cout << "[" << i << "]" << s[i] << '\n';
	}

	return 0;
}
