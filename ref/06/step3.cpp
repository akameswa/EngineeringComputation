#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>

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

bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th)
{
	return (tx<=mx && mx<=tx+tw && ty<=my && my<=ty+th);
}

#define NUM_PARTICLES 200
#define NUM_TARGETS 5

int main(void)
{
	int x=400,y=550;
	int mx,my,mv=8;
	bool mState=false;

	int tx[NUM_TARGETS],ty[NUM_TARGETS],tw[NUM_TARGETS],th[NUM_TARGETS],tv[NUM_TARGETS];
	bool tState[NUM_TARGETS];

	srand(time(nullptr));


	bool eState=false;
	int eStep=0;
	int ex[NUM_PARTICLES],ey[NUM_PARTICLES],evx[NUM_PARTICLES],evy[NUM_PARTICLES];

	for(int i=0; i<NUM_TARGETS; ++i)
	{
		tState[i]=true;
		tx[i]=0;
		ty[i]=80+rand()%40;
		tw[i]=100;
		th[i]=25;
		tv[i]=10+rand()%20;
	}




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
		for(int i=0; i<NUM_TARGETS; ++i)
		{
			if(true==tState[i])
			{
				tx[i]+=tv[i];
				if(800<tx[i])
				{
					tx[i]=0;
				}
			}
		}

		for(int i=0; i<NUM_TARGETS; ++i)
		{
			if(true==mState &&
			   true==tState[i] &&
			   true==CheckCollision(mx,my,tx[i],ty[i],tw[i],th[i]))
			{
				tState[i]=false;
				mState=false;

				eState=true;
				eStep=0;
				for(int i=0; i<NUM_PARTICLES; ++i)
				{
					ex[i]=mx;
					ey[i]=my;
					evx[i]=rand()%51-25;
					evy[i]=rand()%51-25;
				}
			}
		}

		if(true==eState)
		{
			for(int i=0; i<NUM_PARTICLES; ++i)
			{
				ex[i]+=evx[i];
				ey[i]+=evy[i];
			}
			++eStep;
			if(100<eStep)
			{
				eState=false;

				bool stillAlive=false;
				for(int i=0; i<NUM_TARGETS; ++i)
				{
					if(true==tState[i])
					{
						stillAlive=true;
						break;
					}
				}
				if(true!=stillAlive)
				{
					break;
				}
			}
		}


		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		DrawSpaceShip(x,y);

		if(true==mState)
		{
			DrawMissile(mx,my);
		}
		for(int i=0; i<NUM_TARGETS; ++i)
		{
			if(true==tState[i])
			{
				DrawTarget(tx[i],ty[i],tw[i],th[i]);
			}
		}
		if(true==eState)
		{
			glColor3f(1,0,0);
			glPointSize(2);
			glBegin(GL_POINTS);
			for(int i=0; i<NUM_PARTICLES; ++i)
			{
				glVertex2i(ex[i],ey[i]);
			}
			glEnd();
		}

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
