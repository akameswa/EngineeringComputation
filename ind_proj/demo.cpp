#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <cmath>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

void DrawTitle(const char* title)
{
    glColor3ub(255, 255, 255);
    int textWidth = strlen(title) * 20; 
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap20x32(title);
}

void DrawGoal()
{
    glColor3ub(255, 255, 255);
    const char* goal = "Goal: Reach the end";
    int textWidth = strlen(goal) * 16; 
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(goal);
}

void DrawLandscape(int mikasa_x)
{
    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
    glVertex2i(0, WINDOW_HEIGHT - 100);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT - 100);
    glEnd();

    // Draw "START" board only if Mikasa is on screen
    if (mikasa_x < WINDOW_WIDTH)
    {
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
        glVertex2i(20, WINDOW_HEIGHT - 300);
        glVertex2i(170, WINDOW_HEIGHT - 300);
        glVertex2i(170, WINDOW_HEIGHT - 230);
        glVertex2i(20, WINDOW_HEIGHT - 230);
        glEnd();
        
        glRasterPos2i(55, WINDOW_HEIGHT - 260);
        YsGlDrawFontBitmap16x24("START");
    }
}

void DrawStickFigure(int x, int y)
{
    glColor3ub(255, 255, 255);
    // Head
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 64; ++i)
    {
        double angle = i * 3.1415926 * 2.0 / 64.0;
        double xx = x + std::cos(angle) * 10.0;
        double yy = y - 40 + std::sin(angle) * 10.0;
        glVertex2d(xx, yy);
    }
    glEnd();

    // Body
    glBegin(GL_LINES);
    glVertex2i(x, y - 30);
    glVertex2i(x, y);
    // Arms
    glVertex2i(x - 20, y - 15);
    glVertex2i(x + 20, y - 15);
    // Legs
    glVertex2i(x, y);
    glVertex2i(x - 10, y + 30);
    glVertex2i(x, y);
    glVertex2i(x + 10, y + 30);
    glEnd();
}

void SetBackgroundColor()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
}

void DrawTimer(double seconds)
{
    glColor3ub(255, 255, 255);
    char timerText[20];
    sprintf(timerText, "Time: %.1f", seconds);
    glRasterPos2i(WINDOW_WIDTH - 150, 30);
    YsGlDrawFontBitmap16x24(timerText);
}

void DrawObstacle()
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 300); 
    glVertex2i(WINDOW_WIDTH / 2 + 25, WINDOW_HEIGHT - 300); 
    glVertex2i(WINDOW_WIDTH / 2 + 25, WINDOW_HEIGHT - 100); 
    glVertex2i(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 100);     
    glEnd();
}

void DrawSpeechBubble(int x, int y)
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y - 90);  
    glVertex2i(x + 80, y - 90);  
    glVertex2i(x + 80, y - 40);
    glVertex2i(x + 20, y - 40);
    glVertex2i(x, y - 30);
    glVertex2i(x, y - 90);  
    glEnd();
    
    glRasterPos2i(x + 20, y - 55);  
    YsGlDrawFontBitmap16x24("Yes");
}

void DrawObstacleText()
{
    glColor3ub(255, 255, 255);
    const char* text = "Challenge obstacle?";
    int textWidth = strlen(text) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(text);
}

int main()
{
    FsOpenWindow(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    SetBackgroundColor();

    int state = 0;
    clock_t start_time = clock();
    int mikasa_x = 50;
    bool obstacle_visible = false;
    bool text_visible = false;
    bool speech_bubble_visible = false;
    double total_elapsed_seconds = 0.0;
    double mikasa_movement_time = 0.0;
    double state_timer = 0.0;

    while (true)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double elapsed_seconds = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        total_elapsed_seconds += elapsed_seconds;
        state_timer += elapsed_seconds;
        start_time = clock();

        DrawTimer(total_elapsed_seconds);

        switch (state)
        {
        case 0: // Title
            DrawTitle("Journey of Mikasa");
            DrawStickFigure(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);
            break;
        case 1: // Goal
            DrawGoal();
            break;
        case 2: // Landscape with Mikasa moving
            mikasa_movement_time += elapsed_seconds;
            mikasa_x = 50 + (int)(mikasa_movement_time * 200); 
            DrawLandscape(mikasa_x);
            if (mikasa_x < WINDOW_WIDTH)
            {
                DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            }
            else
            {
                state = 3;
                mikasa_x = 50; // Reset Mikasa's position for the obstacle scenario
                mikasa_movement_time = 0.0; // Reset movement time for the next state
                state_timer = 0.0; // Reset state timer
            }
            break;
        case 3: // Obstacle scenario
            DrawLandscape(WINDOW_WIDTH + 1); 
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            DrawObstacle();
            
            if (state_timer > 1.0 && !text_visible)
            {
                text_visible = true;
            }
            if (text_visible)
            {
                DrawObstacleText();
            }
            
            if (state_timer > 2.0 && !speech_bubble_visible)
            {
                speech_bubble_visible = true;
            }
            if (speech_bubble_visible)
            {
                DrawSpeechBubble(mikasa_x + 20, WINDOW_HEIGHT - 100);
            }
            
            if (state_timer > 4.0)
            {
                state = 4; 
                state_timer = 0.0; 
            }
            break;
        case 4: // Final state
            // Add any final state logic here
            break;
        }

        if (state_timer > 2.0 && state < 2)
        {
            state++;
            state_timer = 0.0; 
        }

        FsSwapBuffers();
        FsSleep(16);
    }

    return 0;
}
