#include "fssimplewindow.h"
#include "shoot.h"
#include <stdlib.h>
#include <time.h>

const unsigned int NUM_PARTICLES=200;
const unsigned int NUM_TARGETS=3;
const unsigned int NUM_MISSILES=3;

int main(void)
{
	srand(time(nullptr));


	SpaceShip spaceShip;
	spaceShip.Initialize();


	Missile M[NUM_MISSILES];
	for(auto &m : M)
	{
		m.Initialize();
	}

	Target T[NUM_TARGETS];
	for(auto &t : T)
	{
		t.Initialize();
	}

	int eStep=0;
	bool eState=false;
	Particle P[NUM_PARTICLES];
	for(auto &p : P)
	{
		p.Initialize();
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

		spaceShip.Move(key);

		switch(key)
		{
		case FSKEY_SPACE:
			for(auto &m : M)
			{
				if(true!=m.state)
				{
					m.Launch(spaceShip.x,spaceShip.y);
					break;
				}
			}
			break;
		}

		for(auto &m : M)
		{
			if(true==m.state)
			{
				m.MoveUp();
				if(m.y<0)
				{
					m.Terminate();
				}
			}
		}
		for(auto &t : T)
		{
			if(true==t.state)
			{
				t.MoveRight();
			}
		}

		for(auto &t : T)
		{
			for(auto &m : M)
			{
				if(true==m.state &&
				   true==t.state &&
				   true==CheckCollision(m.x,m.y,t.x,t.y,t.w,t.h))
				{
					t.Terminate();
					m.Terminate();

					eState=true;
					eStep=0;
					for(auto &p : P)
					{
						p.Start(m.x,m.y);
					}
				}
			}
		}

		if(true==eState)
		{
			for(auto &p : P)
			{
				p.Move();
			}
			++eStep;
			if(100<eStep)
			{
				eState=false;

				bool stillAlive=false;
				for(auto t : T)
				{
					if(true==t.state)
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

		spaceShip.Draw();

		for(auto &m : M)
		{
			if(true==m.state)
			{
				m.Render();
			}
		}
		for(auto &t : T)
		{
			if(true==t.state)
			{
				t.Render();
			}
		}
		if(true==eState)
		{
			glColor3f(1,0,0);
			glPointSize(2);
			glBegin(GL_POINTS);
			for(auto &p : P)
			{
				glVertex2i(p.x,p.y);
			}
			glEnd();
		}

		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}
