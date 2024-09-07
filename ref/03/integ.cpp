#include <iostream>



double Function(double x)
{
	return x*x;
}

double Integrate(double x0,double x1,double step)
{
	double sum=0.0;
	for(auto x=x0; x<x1; x+=step)
	{
		auto y=Function(x);
		auto area=step*y;
		sum+=area;
	}
	return sum;
}

int main(void)
{
	std::cout << "Enter x0 x1 Step:";

	double x0,x1,step;
	std::cin >> x0 >> x1 >> step;

	std::cout << "Integration is " << Integrate(x0,x1,step) << "\n";

	return 0;
}
