#include "solver.h"

void Solver::SolveLinearSimultaneousEquation(
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

