#include "fssimplewindow.h"
#include <stdlib.h>
#include <math.h>

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

int main(void)
{
	FsOpenWindow(0,0,800,600,0);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		int x0=rand()%800;
		int y0=rand()%600;
		int ra=rand()%800;
		int r=rand()%256;
		int g=rand()%256;
		int b=rand()%256;

		glColor3ub(r,g,b);
		DrawCircle(x0,y0,ra);

		glFlush();
	}
}
