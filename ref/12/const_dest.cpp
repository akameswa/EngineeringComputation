#include <iostream>

class SampleClass
{
public:
	SampleClass()
	{
		std::cout << __FUNCTION__ << "\n";
	}
	~SampleClass()
	{
		std::cout << __FUNCTION__ << "\n";
	}
};

void Function(void)
{
}

int main(void)
{
	SampleClass a;
	std::cout << "Start\n";
	std::cout << "End\n";
	return 0;
}
