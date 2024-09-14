#include "fssimplewindow.h"
#include <stdlib.h>

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
		int x1=rand()%800;
		int y1=rand()%600;
		int r=rand()%256;
		int g=rand()%256;
		int b=rand()%256;

		glColor3ub(r,g,b);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2i(x0,y0);
		glVertex2i(x1,y0);
		glVertex2i(x1,y1);
		glVertex2i(x0,y1);
		glEnd();

		glFlush();
	}
}
