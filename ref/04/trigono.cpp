#include <stdio.h>
#include <math.h>

int main(void)
{
	double deg;
	printf("Enter angle in degree:");
	scanf("%lf",&deg);
	printf("%lf degree is %lf radian\n",deg,deg*3.14/180.0);
	printf("sin(%lf degree) is %lf\n",deg,sin(deg*3.14/180.0));
	printf("cos(%lf degree) is %lf\n",deg,cos(deg*3.14/180.0));
	printf("tan(%lf degree) is %lf\n",deg,tan(deg*3.14/180.0));

	return 0;
}
