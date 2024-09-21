#include "fssimplewindow.h"

int main(void)
{
	FsOpenWindow(0,0,800,600,1);

	int x=0,y=0;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); // It makes alpha as solidness or opaqueness.

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		switch(key)
		{
		case FSKEY_LEFT:
			x-=10;
			break;
		case FSKEY_RIGHT:
			x+=10;
			break;
		case FSKEY_UP:
			y-=10;
			break;
		case FSKEY_DOWN:
			y+=10;
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

		glColor4f(0,0,1,0.5);
		glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x+100,y);
		glVertex2i(x+100,y+100);
		glVertex2i(x,y+100);
		glEnd();

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
	}
}
