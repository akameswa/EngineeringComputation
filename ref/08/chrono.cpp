#include "fssimplewindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <chrono>

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

void Bounce(double x1,double y1,double &vx1,double &vy1,
            double x2,double y2,double &vx2,double &vy2)
{
	double dx,dy;
	dx=x2-x1;
	dy=y2-y1;

	double LL=dx*dx+dy*dy;
	double L=sqrt(LL);

	if(0.000001<L && L<2.0) // No division by zero, two balls are close to each other
	{
		double dvx,dvy;
		dvx=vx2-vx1;
		dvy=vy2-vy1;

		double dot=dx*dvx+dy*dvy;
		if(dot<0.0) // Two balls are closing in.
		{
			double nx=dx/L;
			double ny=dy/L;

			double k1=vx1*nx+vy1*ny;
			double k2=vx2*nx+vy2*ny;

			vx1+=nx*(k2-k1);
			vy1+=ny*(k2-k1);

			vx2-=nx*(k2-k1);
			vy2-=ny*(k2-k1);

			// Uncomment for energy-loss simulation
			// vx1*=0.9;
			// vy1*=0.9;
			// vx2*=0.9;
			// vy2*=0.9;
		}
	}
}

#define NUM_BALLS 200

int main(void)
{
	double x[NUM_BALLS],y[NUM_BALLS],vx[NUM_BALLS],vy[NUM_BALLS];
	double g=9.8;

	for(int i=0; i<NUM_BALLS; ++i)
	{
		x[i]=(double)(rand()%41-20);
		y[i]=(double)(rand()%41+20);
		vx[i]=(double)(rand()%21-10);
		vy[i]=(double)(rand()%11-5);
	}


	auto t0=std::chrono::high_resolution_clock::now();


	int ctr=0;
	double dtrec[10];


	FsOpenWindow(0,0,800,600,1);
	for(;;)
	{
		auto t1=std::chrono::high_resolution_clock::now();
		unsigned int ms=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
		double dt=(double)ms/1000.0;
		t0=t1;

		if(0.1<dt)
		{
			dt=0.1;
		}



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

		for(int i=0; i<NUM_BALLS; ++i)
		{
			for(int j=i+1; j<NUM_BALLS; ++j)
			{
				Bounce(x[i],y[i],vx[i],vy[i],x[j],y[j],vx[j],vy[j]);
			}
		}

		int lb,mb,rb,mx,my;
		FsGetMouseEvent(lb,mb,rb,mx,my);


		int wid,hei;
		FsGetWindowSize(wid,hei);
		glViewport(0,0,wid,hei);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,wid,hei,0,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		for(int i=0; i<NUM_BALLS; ++i)
		{
			double sx,sy;
			sx=400.0+x[i]*10.0;
			sy=600.0-y[i]*10.0;
			DrawCircle(sx,sy,1.0*10.0);
		}

		glBegin(GL_LINE_LOOP);
		glVertex2i(mx-10,my);
		glVertex2i(mx,my-10);
		glVertex2i(mx+10,my);
		glVertex2i(mx,my+10);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
