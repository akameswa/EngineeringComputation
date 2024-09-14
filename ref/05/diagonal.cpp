#include "fssimplewindow.h"
#include <stdlib.h>

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

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2i(0,0);
		glVertex2i(800,600);
		glEnd();

		FsSwapBuffers();
	}
}
