#include "fssimplewindow.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double YsPI=3.1415927;

void DrawCircle(double cx,double cy,double r)
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		double x=cx+cos(a)*r;
		double y=cy+sin(a)*r;

		glVertex2d(x,y);
	}
	glEnd();
}

void BounceOnWalls(double x,double y,double &vx,double &vy)
{
	if((x<=-39.0 && vx<0.0) || (39.0<=x && 0.0<vx))
	{
		vx=-vx;
	}
	if(y<=1.0 && vy<0.0)
	{
		vy=-vy;
	}
}

#define NUM_BALLS 20

int main(void)
{
	double x[NUM_BALLS],y[NUM_BALLS],vx[NUM_BALLS],vy[NUM_BALLS];
	double dt=0.025;
	double g=9.8;

	for(int i=0; i<NUM_BALLS; ++i)
	{
		x[i]=(double)(rand()%41-20);
		y[i]=(double)(rand()%41+20);
		vx[i]=(double)(rand()%21-10);
		vy[i]=(double)(rand()%11-5);
	}


	FsOpenWindow(0,0,800,600,1);
	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}


		for(int i=0; i<NUM_BALLS; ++i)
		{
			x[i]=x[i]+vx[i]*dt;
			y[i]=y[i]+vy[i]*dt;
			vx[i]=vx[i];
			vy[i]=vy[i]-g*dt;
			BounceOnWalls(x[i],y[i],vx[i],vy[i]);
		}




		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		for(int i=0; i<NUM_BALLS; ++i)
		{
			double sx,sy;
			sx=400.0+x[i]*10.0;
			sy=600.0-y[i]*10.0;
			DrawCircle(sx,sy,1.0*10.0);
		}

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
