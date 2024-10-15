#include "fssimplewindow.h"
#include "shoot.h"
#include <stdlib.h>



void SpaceShip::Initialize(void)
{
	x=400;
	y=550;
}

void SpaceShip::Move(int key)
{
	switch(key)
	{
	case FSKEY_LEFT:
		x-=10;
		break;
	case FSKEY_RIGHT:
		x+=10;
		break;
	}
}

void SpaceShip::Draw(void)
{
	glColor3ub(0,0,0);
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

bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th)
{
	return (tx<=mx && mx<=tx+tw && ty<=my && my<=ty+th);
}
