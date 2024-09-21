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

		glBegin(GL_QUADS);

		glColor3f(1,0,0);
		glVertex2i(0,0);

		glColor3f(0,1,0);
		glVertex2i(800,0);

		glColor3f(0,0,1);
		glVertex2i(800,600);

		glColor3f(1,1,1);
		glVertex2i(0,600);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
	}
}
