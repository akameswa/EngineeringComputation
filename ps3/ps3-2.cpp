#include "fssimplewindow.h"
#include <math.h>

const double PI = 3.14159265358979323846;

void DrawCircle(int centerX, int centerY, int radius)
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<64; ++i)
    {
        double angle = (double)i*PI/32.0;
        double x = (double)centerX+cos(angle)*(double)radius;
        double y = (double)centerY+sin(angle)*(double)radius;
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawGirl(int x, int y)
{
    // Head
    glColor3ub(255, 200, 200);
    DrawCircle(x, y-50, 30);

    // Body
    glColor3ub(255, 100, 100);
    glBegin(GL_LINES);
    glVertex2i(x, y-20);
    glVertex2i(x, y+50);

    // Arms
    glVertex2i(x, y);
    glVertex2i(x-40, y+20);
    glVertex2i(x, y);
    glVertex2i(x+40, y+20);

    // Legs
    glVertex2i(x, y+50);
    glVertex2i(x-30, y+100);
    glVertex2i(x, y+50);
    glVertex2i(x+30, y+100);
    glEnd();

    // Eyes
    glColor3ub(0, 0, 0);
    DrawCircle(x-10, y-55, 5);
    DrawCircle(x+10, y-55, 5);

    // Mouth
    glBegin(GL_LINES);
    glVertex2i(x-10, y-35);
    glVertex2i(x+10, y-35);
    glEnd();
}

void DrawHut(int x, int y)
{
    // Walls
    glColor3ub(150, 75, 0);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x+100, y);
    glVertex2i(x+100, y-80);
    glVertex2i(x, y-80);
    glEnd();

    // Roof
    glColor3ub(100, 50, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(x-10, y-80);
    glVertex2i(x+50, y-130);
    glVertex2i(x+110, y-80);
    glEnd();

    // Door
    glColor3ub(100, 50, 0);
    glBegin(GL_QUADS);
    glVertex2i(x+40, y);
    glVertex2i(x+60, y);
    glVertex2i(x+60, y-40);
    glVertex2i(x+40, y-40);
    glEnd();
}

void DrawMountain(int x, int y)
{
    glColor3ub(100, 100, 100);
    glBegin(GL_TRIANGLES);
    glVertex2i(x, y);
    glVertex2i(x+200, y-150);
    glVertex2i(x+400, y);
    glEnd();

    // Snow cap
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLES);
    glVertex2i(x+180, y-135);
    glVertex2i(x+200, y-150);
    glVertex2i(x+220, y-135);
    glEnd();
}

void DrawSun(int x, int y)
{
    glColor3ub(255, 255, 0);
    DrawCircle(x, y, 40);

    // Sun rays
    glBegin(GL_LINES);
    for(int i=0; i<8; ++i)
    {
        double angle = i * PI / 4;
        glVertex2i(x, y);
        glVertex2i(x + cos(angle)*60, y + sin(angle)*60);
    }
    glEnd();
}

void DrawLand()
{   
    // Forest Green
    glColor3ub(34, 139, 34);  
    glBegin(GL_QUADS);
    glVertex2i(0, 600);
    glVertex2i(800, 600);
    glVertex2i(800, 400);
    glVertex2i(0, 400);
    glEnd();
}

int main(void)
{
    FsOpenWindow(0, 0, 800, 600, 1);

    for(;;)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Sky
        glColor3ub(135, 206, 235);  
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(800, 0);
        glVertex2i(800, 400);
        glVertex2i(0, 400);
        glEnd();

        DrawLand();
        DrawMountain(100, 400);
        DrawSun(700, 100);
        DrawHut(500, 400);
        DrawGirl(300, 400);

        FsSwapBuffers();
        FsSleep(20);

        FsPollDevice();
        auto key = FsInkey();
        if(FSKEY_ESC == key)
        {
            break;
        }
    }

    return 0;
}