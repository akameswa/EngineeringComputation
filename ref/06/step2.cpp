#include "fssimplewindow.h"

void DrawSpaceShip(int x,int y)
{
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex2i(x-5,y-19);
	glVertex2i(x+4,y-19);
	glVertex2i(x+4,y);
	glVertex2i(x-5,y);

	glVertex2i(x-15,y-9);
	glVertex2i(x+14,y-9);
	glVertex2i(x+14,y);
	glVertex2i(x-15,y);
	glEnd();
}

void DrawMissile(int x,int y)
{
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2i(x,y);
	glVertex2i(x,y+10);
	glEnd();
}

void DrawTarget(int x,int y,int w,int h)
{
	glColor3f(0,1,1);
	glBegin(GL_QUADS);
	glVertex2i(x,y);
	glVertex2i(x+w,y);
	glVertex2i(x+w,y+h);
	glVertex2i(x,y+h);
	glEnd();
}

int main(void)
{
	int x=400,y=550;
	int mx,my,mv=8;
	bool mState=false;
	int tx,ty,tv=20;
	bool tState=true;


	tx=0;
	ty=100;


	FsOpenWindow(0,0,800,600,1);
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
		case FSKEY_SPACE:
			if(true!=mState)
			{
				mState=true;
				mx=x;
				my=y;
			}
			break;
		}

		if(true==mState)
		{
			my-=mv;
			if(my<0)
			{
				mState=false;
			}
		}
		if(true==tState)
		{
			tx+=tv;
			if(800<tx)
			{
				tx=0;
			}
		}


		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		DrawSpaceShip(x,y);

		if(true==mState)
		{
			DrawMissile(mx,my);
		}
		if(true==tState)
		{
			DrawTarget(tx,ty,80,20);
		}

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
