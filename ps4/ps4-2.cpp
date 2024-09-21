#include <stdio.h>
#include "fssimplewindow.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double PI = 3.14159265;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const double GRAVITY = 98;
const double DT = 0.025;

const int CANNON_X = 50;
const int CANNON_Y = WINDOW_HEIGHT - 50;
const int CANNON_SIZE = 20;
const int BARREL_LENGTH = 30;
const double INITIAL_SPEED = 400;  // 40 m/sec * 10 pixels/meter

const int TAIL_LENGTH = 10;
const int NUM_OBSTACLES = 5;

void DrawCannon(double angle)
{
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
    glVertex2i(CANNON_X - CANNON_SIZE/2, CANNON_Y + CANNON_SIZE/2);
    glVertex2i(CANNON_X + CANNON_SIZE/2, CANNON_Y + CANNON_SIZE/2);
    glVertex2i(CANNON_X + CANNON_SIZE/2, CANNON_Y - CANNON_SIZE/2);
    glVertex2i(CANNON_X - CANNON_SIZE/2, CANNON_Y - CANNON_SIZE/2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(CANNON_X, CANNON_Y);
    glVertex2i(CANNON_X + BARREL_LENGTH * cos(-angle * PI / 180), 
               CANNON_Y + BARREL_LENGTH * sin(-angle * PI / 180));
    glEnd();
}

void DrawCannonball(double x, double y, int cannonballCount, double tailX[], double tailY[])
{
    // Set color based on cannonballCount
    switch (cannonballCount)
    {
        case 1: glColor3f(0, 0, 1); break;    // Blue
        case 2: glColor3f(0, 1, 1); break;    // Cyan
        case 3: glColor3f(1, 1, 0); break;    // Yellow
        case 4: glColor3f(1, 0, 1); break;    // Magenta
        default: glColor3f(1, 0, 0); break;   // Red
    }

    // Draw the cannonball
    glBegin(GL_POLYGON);
    for (int i = 0; i < 64; i++)
    {
        double angle = (double)i * PI / 32.0;
        glVertex2d(x + cos(angle) * 5, y + sin(angle) * 5);
    }
    glEnd();

    // Draw the tail
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < TAIL_LENGTH; i++)
    {
        if (tailX[i] != 0 || tailY[i] != 0)
        {
            glVertex2d(tailX[i], tailY[i]);
        }
    }
    glEnd();
}

void MoveCannonball(double &x, double &y, double &vx, double &vy)
{
    // Simple Euler integration
    x += vx * DT;
    y += vy * DT;
    vy += GRAVITY * DT;
}

void DrawTarget(double x, double y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + 100, y);
    glVertex2i(x + 100, y + 100);
    glVertex2i(x, y + 100);
    glEnd();
}

void MoveTarget(double &y, double &vy)
{
    y += vy * DT;  
    if (y <= 0 || y >= WINDOW_HEIGHT - 100) 
    {
        vy = -vy;  
        y += vy * DT;  
    }
}

void DrawObstacle(int x, int y, int w, int h, int hits)
{
    if (hits == 0) glColor3f(0, 1, 0);         // Green
    else if (hits == 1) glColor3f(1, 1, 0);    // Yellow

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();
}

bool CheckCollision(double x1, double y1, double x2, double y2, double w, double h)
{
    return (x1 >= x2 && x1 <= x2 + w && y1 >= y2 && y1 <= y2 + h);
}

int main(void)
{
    FsOpenWindow(16, 16, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    srand(time(NULL));

    double cannonAngle = 45.0;
    double cannonballX, cannonballY, cannonballVx, cannonballVy;
    bool cannonballActive = false;
    int cannonballCount = 0;

    double targetY = WINDOW_HEIGHT - 600;  // Initially 60m high from bottom
    double targetVy = -100;  // 10 m/sec downward

    int obstacles[NUM_OBSTACLES][5];  // [x, y, w, h, hits]
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        obstacles[i][2] = 80 + rand() % 71;   // w (8m to 15m)
        obstacles[i][3] = 80 + rand() % 71;   // h (8m to 15m)
        
        // Ensure the obstacle is fully within the window and doesn't overlap with the cannon
        int minX = CANNON_X + CANNON_SIZE + 10; // Add some padding
        int maxX = WINDOW_WIDTH - obstacles[i][2];
        obstacles[i][0] = minX + rand() % (maxX - minX);  // x
        
        int maxY = WINDOW_HEIGHT - obstacles[i][3];
        obstacles[i][1] = rand() % maxY;  // y
        
        obstacles[i][4] = 0;  // hits
    }

    double tailX[TAIL_LENGTH] = {0};
    double tailY[TAIL_LENGTH] = {0};
    int tailIndex = 0;

    for (;;)
    {
        FsPollDevice();
        int key = FsInkey();
        if (key == FSKEY_ESC) break;

        if (key == FSKEY_UP && cannonAngle < 90) cannonAngle += 3;
        if (key == FSKEY_DOWN && cannonAngle > 0) cannonAngle -= 3;

        if (key == FSKEY_SPACE && !cannonballActive)
        {
            cannonballActive = true;
            cannonballCount++;
            cannonballX = CANNON_X + BARREL_LENGTH * cos(-cannonAngle * PI / 180);
            cannonballY = CANNON_Y + BARREL_LENGTH * sin(-cannonAngle * PI / 180);
            cannonballVx = INITIAL_SPEED * cos(-cannonAngle * PI / 180);
            cannonballVy = INITIAL_SPEED * sin(-cannonAngle * PI / 180);

            // Reset the tail when a new cannonball is fired
            for (int i = 0; i < TAIL_LENGTH; i++)
            {
                tailX[i] = 0;
                tailY[i] = 0;
            }
            tailIndex = 0;
        }

        if (cannonballActive)
        {
            MoveCannonball(cannonballX, cannonballY, cannonballVx, cannonballVy);
            if (cannonballX > WINDOW_WIDTH || cannonballY > WINDOW_HEIGHT) cannonballActive = false;

            // Update tail positions
            tailX[tailIndex] = cannonballX;
            tailY[tailIndex] = cannonballY;
            tailIndex = (tailIndex + 1) % TAIL_LENGTH;

            // Check collision with obstacles
            for (int i = 0; i < NUM_OBSTACLES; i++)
            {
                if (CheckCollision(cannonballX, cannonballY, obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3]))
                {
                    obstacles[i][4]++;
                    cannonballActive = false;
                    if (obstacles[i][4] >= 2) obstacles[i][2] = obstacles[i][3] = 0;  // Remove obstacle
                    break;
                }
            }

            // Check collision with target
            if (CheckCollision(cannonballX, cannonballY, WINDOW_WIDTH - 100, targetY, 100, 100))
            {
                printf("Target hit! Cannonballs fired: %d\n", cannonballCount);
                break;
            }
        }

        MoveTarget(targetY, targetVy);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawCannon(cannonAngle);
        if (cannonballActive) DrawCannonball(cannonballX, cannonballY, cannonballCount, tailX, tailY);

        for (int i = 0; i < NUM_OBSTACLES; i++)
        {
            DrawObstacle(obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3], obstacles[i][4]);
        }

        DrawTarget(WINDOW_WIDTH - 100, targetY);

        FsSwapBuffers();
        FsSleep(20);
    }

    return 0;
}