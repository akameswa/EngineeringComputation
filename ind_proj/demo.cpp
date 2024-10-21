#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <cmath>
#include <ctime>
#include <algorithm>

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set to black
}

void DrawTimer(double seconds)
{
    glColor3ub(255, 255, 255);
    char timerText[20];
    sprintf(timerText, "Time: %.1f", seconds);
    int textWidth = strlen(timerText) * 16; // Assuming 16 pixels per character
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, 30);
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

void DrawSpaceShip(int x,int y)
{
    glColor3ub(255,255,255);  
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

void DrawMissile(int x,int y)
{
    glColor3ub(255,255,255);  
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
    glColor3ub(255,0,0);  
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

void DrawUFO(int x,int y)
{
    glColor3ub(255,255,255);  
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

bool CheckCollision(int mx, int my, int tx, int ty)
{
    return (tx-20 <= mx && mx <= tx+40 && ty-20 <= my && my <= ty+25);
}

void DrawEnteringEffect(double elapsed_time)
{
    int flash_count = static_cast<int>(elapsed_time * 4); // 4 flashes per second
    if (flash_count % 2 == 0)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawSpaceGame(int spaceship_x, int spaceship_y, int mikasa_x, int mikasa_y, 
                   bool missile_state, int missile_x, int missile_y,
                   const int tx[], const int ty[], const bool tState[], int num_targets)
{
    DrawSpaceShip(spaceship_x, spaceship_y);
    DrawStickFigure(mikasa_x, mikasa_y);
    
    if (missile_state)
    {
        DrawMissile(missile_x, missile_y);
    }
    
    for (int i = 0; i < num_targets; ++i)
    {
        if (tState[i])
        {
            DrawUFO(tx[i], ty[i]);
        }
    }
}

void DrawEnteringText()
{
    glColor3ub(255, 255, 255);
    const char* text = "Entering obstacle world";
    int textWidth = strlen(text) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(text);
}

void DrawConqueredText()
{
    glColor3ub(255, 255, 255);
    const char* text1 = "Obstacle world conquered.";
    const char* text2 = "Returning back.";
    int textWidth1 = strlen(text1) * 16;
    int textWidth2 = strlen(text2) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth1 / 2, WINDOW_HEIGHT / 2 - 20);
    YsGlDrawFontBitmap16x24(text1);
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth2 / 2, WINDOW_HEIGHT / 2 + 20);
    YsGlDrawFontBitmap16x24(text2);
}

void DrawSteps(int mikasa_x)
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);
    glVertex2i(WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT - 200); 
    glVertex2i(WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT - 200);
    glVertex2i(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT - 200); 
    glEnd();


    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
    glVertex2i(0, WINDOW_HEIGHT - 100);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100); 
    glVertex2i(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT - 200); 
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT - 200); 
    glEnd();
}

void DrawEndTower()
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 200);
    glVertex2i(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT - 200);
    glVertex2i(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT - 300);
    glVertex2i(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 300);
    glEnd();

    glRasterPos2i(WINDOW_WIDTH / 2 + 320, WINDOW_HEIGHT - 250);
    YsGlDrawFontBitmap16x24("END");


    // Flagpole
    glBegin(GL_LINES);
    glVertex2i(WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT - 300);
    glVertex2i(WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT - 350);
    glEnd();

    // Flag
    glBegin(GL_TRIANGLES);
    glVertex2i(WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT - 350);
    glVertex2i(WINDOW_WIDTH / 2 + 380, WINDOW_HEIGHT - 330);
    glVertex2i(WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT - 310);
    glEnd();

}

#define NUM_PARTICLES 200

int main()
{
    FsOpenWindow(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    SetBackgroundColor();

    int state = 0;
    clock_t start_time = clock();
    int mikasa_x = 50;
    double total_elapsed_seconds = 0.0;
    double mikasa_movement_time = 0.0;
    double state_timer = 0.0;

    // Space game variables
    const int NUM_TARGETS = 5;
    int tx[NUM_TARGETS], ty[NUM_TARGETS];
    bool tState[NUM_TARGETS];

    // Initialize target positions evenly distributed
    for (int i = 0; i < NUM_TARGETS; ++i)
    {
        tState[i] = true;
        tx[i] = (i + 1) * (WINDOW_WIDTH / (NUM_TARGETS + 1)); // Evenly distribute targets horizontally
        ty[i] = 100; // All targets at the same height
    }

    int x = tx[0]; // Initialize spaceship at the leftmost target's x position
    int y = WINDOW_HEIGHT - 100;
    int mx, my, mv = 10;
    bool mState = false;

    bool eState = false;
    int eStep = 0;
    int ex[NUM_PARTICLES], ey[NUM_PARTICLES], evx[NUM_PARTICLES], evy[NUM_PARTICLES];

    int current_target = 0;
    double shoot_timer = 0.0;

    while (true)
    {
        FsPollDevice();
        auto key = FsInkey();
        if (key == FSKEY_ESC)
        {
            break;
        }

        double elapsed_seconds = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        total_elapsed_seconds += elapsed_seconds;
        state_timer += elapsed_seconds;
        start_time = clock();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        switch (state)
        {
        case 0: // Title
            DrawTitle("Journey of Mikasa");
            DrawStickFigure(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);
            if (state_timer > 2.0)
            {
                state = 1;
                state_timer = 0.0;
            }
            break;

        case 1: // Goal
            DrawGoal();
            if (state_timer > 2.0)
            {
                state = 2;
                state_timer = 0.0;
            }
            break;

        case 2: // Mikasa moving outside the window
            mikasa_movement_time += elapsed_seconds;
            mikasa_x = 50 + static_cast<int>(mikasa_movement_time * 200); // Adjust speed as needed
            DrawLandscape(mikasa_x);
            if (mikasa_x < WINDOW_WIDTH)
            {
                DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            }
            else
            {
                // Mikasa has moved outside the window; transition to next state
                state = 3;
                mikasa_x = 50; // Reset Mikasa's position
                mikasa_movement_time = 0.0;
                state_timer = 0.0;
            }
            break;

        case 3: // Obstacle appears with Mikasa at initial position
            DrawLandscape(WINDOW_WIDTH + 1); // Draw landscape without Mikasa moving
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100); // Mikasa at initial position
            DrawObstacle();
            state = 4; // Move to the next state in the following frame
            state_timer = 0.0;
            break;

        case 4: // Show "Challenge obstacle?" text
            DrawLandscape(WINDOW_WIDTH + 1); // Ensure landscape is drawn
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100); // Mikasa at initial position
            DrawObstacle();
            DrawObstacleText();
            if (state_timer > 1.0)
            {
                state = 5;
                state_timer = 0.0;
            }
            break;

        case 5: // Show speech bubble
            DrawLandscape(WINDOW_WIDTH + 1);
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            DrawObstacle();
            DrawObstacleText();
            DrawSpeechBubble(mikasa_x + 20, WINDOW_HEIGHT - 100);
            if (state_timer > 1.0)
            {
                state = 6;
                state_timer = 0.0;
            }
            break;

        case 6: // Wait before showing entering text
            DrawLandscape(WINDOW_WIDTH + 1);
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            DrawObstacle();
            DrawObstacleText();
            DrawSpeechBubble(mikasa_x + 20, WINDOW_HEIGHT - 100);
            if (state_timer > 1.0)
            {
                state = 7;
                state_timer = 0.0;
            }
            break;

        case 7: // Show "Entering obstacle world" text
            DrawEnteringText();
            if (state_timer > 2.0)
            {
                state = 8;
                state_timer = 0.0;
            }
            break;

        case 8: // Flashing effect
            DrawEnteringEffect(state_timer);
            if (state_timer > 2.0)
            {
                state = 9;
                state_timer = 0.0;
            }
            break;

        case 9: // Space game
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shoot_timer += elapsed_seconds;

            if (current_target < NUM_TARGETS)
            {
                int target_x = tx[current_target];

                if (x < target_x)
                {
                    x += std::min(5, target_x - x);
                }
                else if (x > target_x)
                {
                    x -= std::min(5, x - target_x);
                }

                if (x == target_x && !mState && shoot_timer >= 1.0)
                {
                    mState = true;
                    mx = x;
                    my = y;
                    shoot_timer = 0.0;
                }
            }

            if (mState)
            {
                my -= mv;
                if (my < 0)
                {
                    mState = false;
                }

                if (CheckCollision(mx, my, tx[current_target], ty[current_target]))
                {
                    tState[current_target] = false;
                    mState = false;
                    current_target++;

                    eState = true;
                    eStep = 0;
                    for (int i = 0; i < NUM_PARTICLES; ++i)
                    {
                        ex[i] = mx;
                        ey[i] = my;
                        evx[i] = rand() % 51 - 25;
                        evy[i] = rand() % 51 - 25;
                    }
                }
            }

            if (eState)
            {
                for (int i = 0; i < NUM_PARTICLES; ++i)
                {
                    ex[i] += evx[i];
                    ey[i] += evy[i];
                }
                ++eStep;
                if (100 < eStep)
                {
                    eState = false;
                }
            }

            glColor3ub(255, 255, 255);
            DrawStickFigure(x, y + 50); 
            DrawSpaceShip(x, y - 50); 

            if (mState)
            {
                DrawMissile(mx, my);
            }

            for (int i = 0; i < NUM_TARGETS; ++i)
            {
                if (tState[i])
                {
                    DrawUFO(tx[i], ty[i]);
                }
            }

            if (eState)
            {
                glColor3f(1, 0, 0);  
                glPointSize(2);
                glBegin(GL_POINTS);
                for (int i = 0; i < NUM_PARTICLES; ++i)
                {
                    glVertex2i(ex[i], ey[i]);
                }
                glEnd();
            }

            if (current_target >= NUM_TARGETS)
            {
                state = 10;
                state_timer = 0.0;
            }
            break;

        case 10: // Show "Obstacle world conquered. Returning back." text
            DrawConqueredText();
            if (state_timer > 2.0)
            {
                state = 11; // Move to final state
                state_timer = 0.0;
            }
            break;

        case 11: // Returning to the obstacle frame, moving right
            DrawLandscape(mikasa_x);
            DrawObstacle();
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
            mikasa_movement_time += elapsed_seconds;
            mikasa_x = 50 + static_cast<int>(mikasa_movement_time * 200);

            if (mikasa_x > WINDOW_WIDTH)
            {
                state = 12;
                mikasa_x = 50; // Reset Mikasa's position
                mikasa_movement_time = 0.0;
            }
            break;

        case 12: // Climbing steps
            DrawSteps(mikasa_x);
            DrawEndTower();

            if (mikasa_x < WINDOW_WIDTH / 2 + 100) {
                DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);
                mikasa_x += 5;
            } else if (mikasa_x < WINDOW_WIDTH / 2 + 200) {
                int y = WINDOW_HEIGHT - 100 - (mikasa_x - (WINDOW_WIDTH / 2 + 100));
                DrawStickFigure(mikasa_x, y);
                mikasa_x += 5;
            }
            else
            {
                DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 200); // Mikasa on top of the steps
                if (mikasa_x < WINDOW_WIDTH / 2 + 300)
                {
                    mikasa_x += 5;
                } else {

                    state = 13;
                    state_timer = 0;
                    for (int i = 0; i < NUM_PARTICLES; ++i) {
                        ex[i] = mikasa_x;
                        ey[i] = WINDOW_HEIGHT - 200;
                        evx[i] = rand() % 51 - 25;
                        evy[i] = rand() % 51 - 25;
                    }
                    eState = true;
                }
            }

            break;
        case 13:
            DrawSteps(mikasa_x);
            DrawEndTower();
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 200);

            if (eState)
            {
                for (int i = 0; i < NUM_PARTICLES; ++i)
                {
                    ex[i] += evx[i];
                    ey[i] += evy[i];
                }
                ++eStep;
                if (100 < eStep)
                {
                    eState = false;
                   break; // Game ends here
                }
            }

            glColor3f(1, 0, 0);
            glPointSize(2);
            glBegin(GL_POINTS);
            for (int i = 0; i < NUM_PARTICLES; ++i)
            {
                glVertex2i(ex[i], ey[i]);
            }
            glEnd();

            break;

        default:
            break;
        }

        // Remove automatic state transitions
        // Each state now handles its own transitions

        // Uncomment the following lines if you want to have automatic transitions for specific states beyond customization
        // if (state < 4 && state_timer > 2.0)
        // {
        //     state++;
        //     state_timer = 0.0;
        // }

        DrawTimer(total_elapsed_seconds);
        FsSwapBuffers();
        FsSleep(16);
    }

    return 0;
}
