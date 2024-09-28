#include "fssimplewindow.h"
#include <stdio.h>

int main(void)
{
	FsOpenWindow(0,0,800,600,1);
	FsPassedTime();

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		int lb,mb,rb,mx,my;
		auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
		if(FSMOUSEEVENT_LBUTTONDOWN==evt)
		{
			printf("Lbutton down.\n");
		}


		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		if(0!=lb)
		{
			glColor3f(1,0,0);
		}
		else
		{
			glColor3f(0,1,0);
		}

		glBegin(GL_TRIANGLE_FAN);
		glVertex2i(mx-10,my-10);
		glVertex2i(mx+10,my-10);
		glVertex2i(mx+10,my+10);
		glVertex2i(mx-10,my+10);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
