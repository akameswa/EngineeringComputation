#include "fssimplewindow.h"

int main(void)
{
	FsOpenWindow(0,0,800,600,1);

	glShadeModel(GL_SMOOTH);

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1,0b1111000011110000);

		glBegin(GL_LINES);
		glVertex2i(0,0);
		glVertex2i(800,600);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
	}
}
