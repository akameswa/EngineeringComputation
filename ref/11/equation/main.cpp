#include <stdio.h>
#include "solver.h"
#include "thirdprog.h" // Future addition of the functionality

int global=0;

int main(void)
{
	global=100;

    printf("This calculates x and y for\n");
    printf("  ax+by+c=0\n");
    printf("  dx+ey+f=0\n");
    printf("Enter a b c d e f:");

    double a,b,c,d,e,f;
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);

	Solver solver;
    double x,y;
    solver.SolveLinearSimultaneousEquation(x,y,a,b,c,d,e,f);
    printf("x=%lf y=%lf\n",x,y);

    return 0;
}

