#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"

const double YS_PI=3.1415927;

void DrawSquare(double angle,double size)
{
    int x,y;
    glBegin(GL_QUADS);
    x=400+(int)(cos(angle)*size);
    y=300+(int)(sin(angle)*size);
    glVertex2i(x,y);
    x=400+(int)(cos(angle+YS_PI*0.5)*size);
    y=300+(int)(sin(angle+YS_PI*0.5)*size);
    glVertex2i(x,y);
    x=400+(int)(cos(angle+YS_PI)*size);
    y=300+(int)(sin(angle+YS_PI)*size);
    glVertex2i(x,y);
    x=400+(int)(cos(angle+YS_PI*1.5)*size);
    y=300+(int)(sin(angle+YS_PI*1.5)*size);
    glVertex2i(x,y);
    glEnd();
}

void DrawTriangle(double angle,double size)
{
    int x,y;
    glBegin(GL_TRIANGLES);
    x=400+(int)(cos(angle+YS_PI/3.0)*size);
    y=300+(int)(sin(angle+YS_PI/3.0)*size);
    glVertex2i(x,y);
    x=400+(int)(cos(angle+YS_PI*3.0/3.0)*size);
    y=300+(int)(sin(angle+YS_PI*3.0/3.0)*size);
    glVertex2i(x,y);
    x=400+(int)(cos(angle+YS_PI*5.0/3.0)*size);
    y=300+(int)(sin(angle+YS_PI*5.0/3.0)*size);
    glVertex2i(x,y);
    glEnd();
}

void DrawScreen(double angle)
{
    glColor3ub(255,0,0);
    DrawSquare(-angle,250.0);
    glColor3ub(0,255,0);
    DrawSquare(angle,200.0);
    glColor3ub(0,0,255);
    DrawTriangle(-angle*2.0,150.0);
    glColor3ub(0,255,255);
    DrawTriangle(angle*2.0,100.0);
}

int main(void)
{
    FsOpenWindow(16,16,800,600,1);

    double angle;
    for(angle=0.0; FsInkey()==0; angle+=0.02)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        DrawScreen(angle);
        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}
