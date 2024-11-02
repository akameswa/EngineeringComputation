#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>


class GameObject
{
public:
	int x,y;
};

class GameObjectWithState : public GameObject
{
public:
	bool state;
};



bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th)
{
	return (tx<=mx && mx<=tx+tw && ty<=my && my<=ty+th);
}

class Missile : public GameObjectWithState
{
public:
	int v;

	void Initialize(void);
	void Launch(int X,int Y);
	void MoveUp(void);
	void Terminate(void);
	void Render(void);
};

void Missile::Launch(int X,int Y)
{
	state=true;
	x=X;
	y=Y;
}
void Missile::MoveUp(void)
{
	y-=v;
}
void Missile::Terminate(void)
{
	state=false;
}
void Missile::Render(void)
{
	glColor3f(0,0,1);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+11,y+-9);
	glVertex2i(x+10,y+19);
	glVertex2i(x+20,y+19);
	glVertex2i(x+20,y+-9);
	glVertex2i(x+17,y+-16);
	glVertex2i(x+15,y+-17);
	glVertex2i(x+13,y+-16);
	glVertex2i(x+11,y+-9);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+11,y+-7);
	glVertex2i(x+6,y+-6);
	glVertex2i(x+6,y+-4);
	glVertex2i(x+10,y+-4);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+20,y+-8);
	glVertex2i(x+23,y+-7);
	glVertex2i(x+24,y+-4);
	glVertex2i(x+20,y+-4);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+9);
	glVertex2i(x+6,y+12);
	glVertex2i(x+6,y+16);
	glVertex2i(x+10,y+18);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+20,y+9);
	glVertex2i(x+25,y+10);
	glVertex2i(x+25,y+16);
	glVertex2i(x+20,y+18);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+15,y+9);
	glVertex2i(x+15,y+16);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+15,y+-8);
	glVertex2i(x+15,y+-5);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+19);
	glVertex2i(x+11,y+29);
	glVertex2i(x+14,y+27);
	glVertex2i(x+16,y+29);
	glVertex2i(x+18,y+26);
	glVertex2i(x+20,y+28);
	glVertex2i(x+20,y+20);
	glEnd();
}

void Missile::Initialize(void)
{
	state=false;
	v=10;
}


class Target : public GameObjectWithState
{
public:
	int w,h,v;

	void Initialize(void);
	void MoveRight(void);
	void Terminate(void);
	void Render(void);
};

void Target::Initialize(void)
{
	state=true;
	x=0;
	y=80+rand()%40;
	w=40;
	h=40;
	v=10+rand()%20;
}

void Target::MoveRight(void)
{
	x+=v;
	if(800<x)
	{
		x=0;
	}
}

void Target::Terminate(void)
{
	state=false;
}

void Target::Render(void)
{
	int x=this->x+w/2;
	int y=this->y+h/2;
	glColor3ub(0,255,0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-9,y+-8);
	glVertex2i(x+8,y+-20);
	glVertex2i(x+25,y+-10);
	glVertex2i(x+-9,y+-8);
	glVertex2i(x+-8,y+5);
	glVertex2i(x+25,y+3);
	glVertex2i(x+24,y+-11);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+5,y+-7);
	glVertex2i(x+2,y+-5);
	glVertex2i(x+2,y+0);
	glVertex2i(x+7,y+1);
	glVertex2i(x+11,y+-1);
	glVertex2i(x+11,y+-5);
	glVertex2i(x+8,y+-7);
	glVertex2i(x+5,y+-7);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-8,y+4);
	glVertex2i(x+-19,y+12);
	glVertex2i(x+-4,y+17);
	glVertex2i(x+8,y+17);
	glVertex2i(x+25,y+13);
	glVertex2i(x+38,y+6);
	glVertex2i(x+24,y+3);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+0,y+17);
	glVertex2i(x+2,y+24);
	glVertex2i(x+9,y+25);
	glVertex2i(x+18,y+23);
	glVertex2i(x+20,y+15);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-15,y+14);
	glVertex2i(x+-14,y+20);
	glVertex2i(x+-7,y+23);
	glVertex2i(x+0,y+20);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+35,y+8);
	glVertex2i(x+33,y+17);
	glVertex2i(x+27,y+21);
	glVertex2i(x+20,y+20);
	glEnd();
}

class Player : public GameObject
{
public:
	void Render(void) const;
};

void Player::Render(void) const
{
	glColor3ub(0,0,255);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-3,y+-15);
	glVertex2i(x+-7,y+12);
	glVertex2i(x+-7,y+43);
	glVertex2i(x+-2,y+46);
	glVertex2i(x+0,y+42);
	glVertex2i(x+8,y+42);
	glVertex2i(x+11,y+46);
	glVertex2i(x+14,y+42);
	glVertex2i(x+14,y+8);
	glVertex2i(x+11,y+-15);
	glVertex2i(x+8,y+-2);
	glVertex2i(x+-1,y+-2);
	glVertex2i(x+-3,y+-15);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-7,y+19);
	glVertex2i(x+-19,y+24);
	glVertex2i(x+-18,y+41);
	glVertex2i(x+-7,y+41);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+14,y+18);
	glVertex2i(x+24,y+22);
	glVertex2i(x+24,y+39);
	glVertex2i(x+14,y+39);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-4,y+25);
	glVertex2i(x+-4,y+39);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+25);
	glVertex2i(x+10,y+37);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+0,y+3);
	glVertex2i(x+-1,y+12);
	glVertex2i(x+0,y+19);
	glVertex2i(x+2,y+21);
	glVertex2i(x+5,y+21);
	glVertex2i(x+7,y+18);
	glVertex2i(x+8,y+11);
	glVertex2i(x+6,y+3);
	glVertex2i(x+4,y+1);
	glVertex2i(x+2,y+1);
	glVertex2i(x+0,y+3);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-1,y+12);
	glVertex2i(x+1,y+15);
	glVertex2i(x+4,y+15);
	glVertex2i(x+7,y+13);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-15,y+22);
	glVertex2i(x+-15,y+17);
	glVertex2i(x+-14,y+22);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+18,y+19);
	glVertex2i(x+19,y+15);
	glVertex2i(x+20,y+20);
	glEnd();
}


class Particle
{
public:
	int x,y,vx,vy;

	void Initialize(void);
	void Start(int x0,int y0);
	void Move(void);
};

void Particle::Initialize(void)
{
}

void Particle::Start(int x0,int y0)
{
	x=x0;
	y=y0;
	vx=rand()%51-25;
	vy=rand()%51-25;
}

void Particle::Move(void)
{
	x+=vx;
	y+=vy;
}


const unsigned int NUM_PARTICLES=200;
const unsigned int NUM_TARGETS=3;
const unsigned int NUM_MISSILES=3;

class ShootingGame
{
public:
	Player player;
	Missile M[NUM_MISSILES];
	Target T[NUM_TARGETS];
	int eStep=0;
	bool eState=false;
	Particle P[NUM_PARTICLES];
	bool terminate=false;
	int x=400,y=550;

	void Initialize(void);
	bool ShouldClose(void);
	void RunOneStep(void);
	void Render(void);
};
void ShootingGame::Initialize(void)
{
	terminate=false;
	player.x=400;
	player.y=550;
	eStep=0;
	for(auto &m : M)
	{
		m.Initialize();
	}

	for(auto &t : T)
	{
		t.Initialize();
	}

	for(auto &p : P)
	{
		p.Initialize();
	}
}
bool ShootingGame::ShouldClose(void)
{
	return terminate;
}
void ShootingGame::RunOneStep(void)
{
	FsPollDevice();

	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		terminate=true;
		return;
	}

	switch(key)
	{
	case FSKEY_LEFT:
		player.x-=10;
		break;
	case FSKEY_RIGHT:
		player.x+=10;
		break;
	case FSKEY_SPACE:
		for(auto &m : M)
		{
			if(true!=m.state)
			{
				m.Launch(player.x,player.y);
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
				terminate=true;
				return;
			}
		}
	}
}
void ShootingGame::Render(void)
{
	player.Render();

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
}

int main(void)
{
	srand(time(nullptr));

	FsOpenWindow(0,0,800,600,1);
	ShootingGame game;
	game.Initialize();
	while(true!=game.ShouldClose())
	{
		game.RunOneStep();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		game.Render();
		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
		FsSleep(25);
	}
}
