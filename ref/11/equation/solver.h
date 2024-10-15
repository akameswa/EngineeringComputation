#ifndef SOLVER_H_IS_INCLUDED
#define SOLVER_H_IS_INCLUDED

class Solver
{
public:
	void SolveLinearSimultaneousEquation(
	    double &x,double &y,
	    double a,double b,double e,
	    double c,double d,double f);
};

extern int global;

#endif
