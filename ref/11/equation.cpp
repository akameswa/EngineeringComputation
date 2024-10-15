#include <stdio.h>

void SolveLinearSimultaneousEquation(
    double &x,double &y,
    double a,double b,double e,
    double c,double d,double f)
// Solve ax+by+e=0     {a b}{x} {-e}    {x} {a b}Inv{-e}  (1/D){ d –b}{-e}
//       cx+dy+f=0     {c d}{y}={-f}    {y}={c d}   {-f}=      {-c  a}{-f}
{
    double D=a*d-b*c;
    x=(1/D)*(-e*d+f*b);
    y=(1/D)*( e*c-f*a);
}

int main(void)
{
    printf("This calculates x and y for\n");
    printf("  ax+by+c=0\n");
    printf("  dx+ey+f=0\n");
    printf("Enter a b c d e f:");

    double a,b,c,d,e,f;
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);

    double x,y;
    SolveLinearSimultaneousEquation(x,y,a,b,c,d,e,f);
    printf("x=%lf y=%lf\n",x,y);

    return 0;
}

