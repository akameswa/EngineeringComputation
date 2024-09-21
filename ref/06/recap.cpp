#include "fssimplewindow.h"

int main(void)
{
	FsOpenWindow(0,0,800,600,1);
	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINES);
		glVertex2i(0,0);
		glVertex2i(800,600);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
	}
}
