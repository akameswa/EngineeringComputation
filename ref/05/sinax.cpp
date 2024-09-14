#include "fssimplewindow.h"
#include <stdlib.h>
#include <math.h>

int main(void)
{
	FsOpenWindow(0,0,800,600,0);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for(double a=0.1; a<=1.0; a+=0.1)
	{
		glBegin(GL_LINE_STRIP);
		for(int x=0; x<800; ++x)
		{
			double X=(double)x/100.0;
			double Y=sin(a*X);

			int y=300-Y*100.0;

			glVertex2i(x,y);
		}
		glEnd();

		glFlush();

		for(;;)
		{
			FsPollDevice();

			auto key=FsInkey();
			if(FSKEY_NULL!=key)
			{
				break;
			}
		}
	}
}
