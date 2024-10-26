#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <cmath>
#include <ctime>
#include <algorithm>
#include "yssimplesound.h"
#include <cstdio>  // For sprintf
#include <cstdlib> // For rand
#include <chrono>  // For time measurement

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

// Draws the title at the center of the window
void DrawTitle(const char* title)
{
    glColor3ub(255, 255, 255);
    int textWidth = strlen(title) * 20; 
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap20x32(title);
}

// Draws the goal text at the center of the window
void DrawGoal()
{
    glColor3ub(255, 255, 255);
    const char* goal = "Goal: Reach the end";
    int textWidth = strlen(goal) * 16; 
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(goal);
}

// Draws the landscape and "START" board if Mikasa is on screen
void DrawLandscape(int mikasa_x)
{
    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
    glVertex2i(0, WINDOW_HEIGHT - 100);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT - 100);
    glEnd();

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

// Draws a stick figure at the specified position
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

    // Body, Arms, and Legs
    glBegin(GL_LINES);
    glVertex2i(x, y - 30); glVertex2i(x, y);
    glVertex2i(x - 20, y - 15); glVertex2i(x + 20, y - 15);
    glVertex2i(x, y); glVertex2i(x - 10, y + 30);
    glVertex2i(x, y); glVertex2i(x + 10, y + 30);
    glEnd();
}

// Sets the background color to black
void SetBackgroundColor()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Draws the timer at the top of the window
void DrawTimer(double seconds)
{
    glColor3ub(255, 255, 255);
    char timerText[20];
    sprintf(timerText, "Time: %.1f", seconds);
    int textWidth = strlen(timerText) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, 30);
    YsGlDrawFontBitmap16x24(timerText);
}

// Draws an obstacle at the center of the window
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

// Draws a speech bubble with "Yes" text
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

// Draws the "Challenge obstacle?" text
void DrawObstacleText()
{
    glColor3ub(255, 255, 255);
    const char* text = "Challenge obstacle?";
    int textWidth = strlen(text) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(text);
}

// Draws a spaceship at the specified position
void DrawSpaceShip(int x, int y)
{
    glColor3ub(255, 255, 255);  
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

// Draws a missile at the specified position
void DrawMissile(int x, int y)
{
    glColor3ub(255, 255, 255);  
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
    glColor3ub(255, 0, 0);  
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

// Draws a UFO at the specified position
void DrawUFO(int x, int y)
{
    glColor3ub(255, 255, 255);  
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

// Checks for collision between missile and target
bool CheckCollision(int mx, int my, int tx, int ty)
{
    return (tx-20 <= mx && mx <= tx+40 && ty-20 <= my && my <= ty+25);
}

// Draws an entering effect with flashing background
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

// Draws the space game elements
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

// Draws the "Entering obstacle world" text
void DrawEnteringText()
{
    glColor3ub(255, 255, 255);
    const char* text = "Entering obstacle world";
    int textWidth = strlen(text) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(text);
}

// Draws the "Obstacle world conquered. Returning back." text
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

// Draws the end board
void DrawEndBoard()
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(WINDOW_WIDTH/2 - 75, WINDOW_HEIGHT - 600);
    glVertex2i(WINDOW_WIDTH/2 + 75, WINDOW_HEIGHT - 600);
    glVertex2i(WINDOW_WIDTH/2 + 75, WINDOW_HEIGHT - 500);
    glVertex2i(WINDOW_WIDTH/2 - 75, WINDOW_HEIGHT - 500);
    glEnd();
    
    glRasterPos2i(WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT - 550);
    YsGlDrawFontBitmap16x24("END");
}

// Draws a diamond at the specified position
void DrawDiamond(int x, int y, int size)
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y - size);        // top
    glVertex2i(x + size, y);        // right
    glVertex2i(x, y + size);        // bottom
    glVertex2i(x - size, y);        // left
    glEnd();
}

// Draws a ramp
void DrawRamp()
{
    glColor3ub(0, 255, 0);  // Green color for the ramp
    glBegin(GL_LINE_STRIP);
    glVertex2i(0, WINDOW_HEIGHT - 100);  // Start from the left edge
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);  // Horizontal part
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);  // Ramp goes up
    glEnd();

    // Green horizontal line at the bottom
    glBegin(GL_LINES);
    glVertex2i(0, WINDOW_HEIGHT - 100);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT - 100);
    glEnd();
}

// Draws the "Destroy targets" text
void DrawDestroyTargetsText()
{
    glColor3ub(255, 255, 255);
    const char* text = "Destroy targets";
    int textWidth = strlen(text) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2);
    YsGlDrawFontBitmap16x24(text);
}

// Draws a refined diamond with internal lines
void DrawRefinedDiamond(int x, int y, int size)
{
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y - size);        // top
    glVertex2i(x + size, y);        // right
    glVertex2i(x, y + size);        // bottom
    glVertex2i(x - size, y);        // left
    glEnd();

    // Internal lines
    glBegin(GL_LINES);
    glVertex2i(x, y - size);        // top to bottom
    glVertex2i(x, y + size);
    glVertex2i(x - size, y);        // left to right
    glVertex2i(x + size, y);

    // Top internal lines
    glVertex2i(x, y - size);
    glVertex2i(x - size / 2, y);
    glVertex2i(x, y - size);
    glVertex2i(x + size / 2, y);

    // Bottom internal lines
    glVertex2i(x - size / 2, y);
    glVertex2i(x, y + size);
    glVertex2i(x + size / 2, y);
    glVertex2i(x, y + size);
    glEnd();
}

// Draws the end message
void DrawEndMessage()
{
    glColor3ub(255, 255, 255);
    const char* text1 = "Goal Reached!";
    int textWidth1 = strlen(text1) * 16;
    glRasterPos2i(WINDOW_WIDTH / 2 - textWidth1 / 2, WINDOW_HEIGHT / 2 + 120);
    YsGlDrawFontBitmap16x24(text1);
}

#define NUM_PARTICLES 200

int main()
{
    FsOpenWindow(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    SetBackgroundColor();

    // Initialize sound player
    YsSoundPlayer player;
    player.Start(); // Start the sound player

    // Declare and load the song
    YsSoundPlayer::SoundData song;
    if(YSOK!=song.LoadWav("song.wav") && YSOK!=song.LoadWav("datafiles/song.wav"))
    {
        printf("Error! Cannot load song.wav!\n");
    }

    // Start playing the song in the background
    player.PlayBackground(song);

    int state = 0;
    auto start_time = std::chrono::steady_clock::now(); // Use chrono for time
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
        tx[i] = (i + 1) * (WINDOW_WIDTH / (NUM_TARGETS + 1));
        ty[i] = 100;
    }

    int x = tx[0];
    int y = WINDOW_HEIGHT - 100;
    int mx, my, mv = 10;
    bool mState = false;

    bool eState = false;
    int eStep = 0;
    int ex[NUM_PARTICLES], ey[NUM_PARTICLES], evx[NUM_PARTICLES], evy[NUM_PARTICLES];

    int current_target = 0;
    double shoot_timer = 0.0;

    const char* obstacle_destroyed_text = "Obstacle destroyed";
    int obstacle_destroyed_text_width = strlen(obstacle_destroyed_text) * 16;

    int mikasa_y = WINDOW_HEIGHT - 100;

    while (true)
    {
        FsPollDevice();

        // Keep the background music playing
        player.KeepPlaying();  // This is crucial for continuous playback

        auto key = FsInkey();
        if (key == FSKEY_ESC)
        {
            break;
        }

        auto current_time = std::chrono::steady_clock::now();
        double elapsed_seconds = std::chrono::duration<double>(current_time - start_time).count();
        total_elapsed_seconds += elapsed_seconds;
        state_timer += elapsed_seconds;
        start_time = current_time;

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
            mikasa_x = 50 + static_cast<int>(mikasa_movement_time * 150); // Slower speed
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

        case 8: // Show "Destroy targets" text with fade
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            if (state_timer < 2.0) {
                // Fade out effect
                int alpha = static_cast<int>(255 * (2.0 - state_timer) / 2.0);
                glColor3ub(255, 255, 255);
                DrawDestroyTargetsText();
            } else {
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

            if (state_timer < 2.0) {
                DrawDestroyTargetsText();
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
            // Draw the original obstacle scene
            DrawLandscape(WINDOW_WIDTH + 1);
            DrawObstacle();
            
            // Draw "Obstacle destroyed" text above the obstacle
            glColor3ub(255, 255, 255);
            glRasterPos2i(WINDOW_WIDTH / 2 - obstacle_destroyed_text_width / 2, WINDOW_HEIGHT - 320);
            YsGlDrawFontBitmap16x24(obstacle_destroyed_text);

            // Move Mikasa from center to right
            mikasa_movement_time += elapsed_seconds;
            mikasa_x = WINDOW_WIDTH/2 + static_cast<int>(mikasa_movement_time * 150);
            DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);

            if (mikasa_x > WINDOW_WIDTH)
            {
                state = 12;
                mikasa_x = 50; // Reset Mikasa's position
                mikasa_movement_time = 0.0;
            }
            break;

        case 12:  // Climbing ramp
            DrawRamp();
            if (mikasa_x < WINDOW_WIDTH / 2) {
                DrawStickFigure(mikasa_x, WINDOW_HEIGHT - 100);  // Moving on horizontal part
                mikasa_x += 5;
            } else if (mikasa_x < WINDOW_WIDTH) {
                mikasa_y = WINDOW_HEIGHT - 100 - (mikasa_x - WINDOW_WIDTH / 2) * 0.5;  // Adjust for ramp slope
                DrawStickFigure(mikasa_x, mikasa_y);
                mikasa_x += 5;
            } else {
                state = 13;
                mikasa_x = 50;  // Reset position for final scene
                mikasa_y = WINDOW_HEIGHT / 2;  // Set to new ground level
                // Initialize particles for the explosion
                eState = true;
                eStep = 0;
                for (int i = 0; i < NUM_PARTICLES; ++i) {
                    ex[i] = WINDOW_WIDTH / 2;
                    ey[i] = WINDOW_HEIGHT / 2;
                    evx[i] = rand() % 21 - 10;
                    evy[i] = rand() % 21 - 10;
                }
            }
            break;

        case 13:  // Final scene with particles and diamond
            // Draw the new horizontal ground line
            glColor3ub(0, 255, 0);
            glBegin(GL_LINES);
            glVertex2i(0, WINDOW_HEIGHT / 2);
            glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
            glEnd();

            DrawEndBoard();

            // Move Mikasa to center
            if (mikasa_x < WINDOW_WIDTH / 2) {
                mikasa_x += 5;
            }

            DrawStickFigure(mikasa_x, mikasa_y);

            // Particle explosion
            if (eState) {
                glColor3f(1, 0, 0);
                glPointSize(2);
                glBegin(GL_POINTS);
                for (int i = 0; i < NUM_PARTICLES; ++i) {
                    ex[i] += evx[i];
                    ey[i] += evy[i];
                    glVertex2i(ex[i], ey[i]);
                }
                glEnd();
                
                eStep++;
                if (eStep > 50) {
                    eState = false;
                    state = 14;
                }
            }
            break;

        case 14:  // Show diamond and end message
            // Draw the new horizontal ground line
            glColor3ub(0, 255, 0);
            glBegin(GL_LINES);
            glVertex2i(0, WINDOW_HEIGHT / 2);
            glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
            glEnd();

            DrawEndBoard();
            DrawStickFigure(WINDOW_WIDTH / 2, mikasa_y);
            DrawRefinedDiamond(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100, 30);

            if (state_timer > 2.0) {
                DrawEndMessage();
            }
            if (state_timer > 8.0) {  // Transition after 4 seconds total
                state = 15;
                state_timer = 0.0;
            }
            break;

        // Add new state for "Song created by Suno AI"
        case 15:  // Hold the final snapshot for 2 more seconds
        {
            // Draw the same elements as in case 14
            glColor3ub(0, 255, 0);
            glBegin(GL_LINES);
            glVertex2i(0, WINDOW_HEIGHT / 2);
            glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
            glEnd();

            DrawEndBoard();
            DrawStickFigure(WINDOW_WIDTH / 2, mikasa_y);
            DrawRefinedDiamond(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100, 30);
            DrawEndMessage();

            if (state_timer > 2.0) {  // Hold for 2 seconds
                state = 16;
                state_timer = 0.0;
            }
            break;
        }

        case 16:  // Display "Song created by Suno AI"
        {
            glColor3ub(0, 0, 0);  // Clear the screen to black
            glClear(GL_COLOR_BUFFER_BIT);

            glColor3ub(255, 255, 255);
            const char* sunoText = "Song created by Suno AI";
            int sunoTextWidth = strlen(sunoText) * 16;
            glRasterPos2i(WINDOW_WIDTH / 2 - sunoTextWidth / 2, WINDOW_HEIGHT / 2);
            YsGlDrawFontBitmap16x24(sunoText);

            if (state_timer > 2.0) {  // Display for 2 seconds
                state = 17;
                state_timer = 0.0;
            }
            break;
        }

        // Add new state for "Created by Adithya"
        case 17: // Display "Created by Adithya"
        {
            glColor3ub(255, 255, 255);
            const char* adithyaText = "Created by Adithya";
            int adithyaTextWidth = strlen(adithyaText) * 16;
            glRasterPos2i(WINDOW_WIDTH / 2 - adithyaTextWidth / 2, WINDOW_HEIGHT / 2);
            YsGlDrawFontBitmap16x24(adithyaText);
            if (state_timer > 2.0) {
                state = 18; // Move to the next state or end
                state_timer = 0.0;
            }
            break;
        }

        // Add new state for "Wait longer to listen to the complete song"
        case 18: // Display "Wait longer to listen to the complete song"
        {
            glColor3ub(255, 255, 255);
            const char* waitText = "Wait longer to listen to the complete song";
            int waitTextWidth = strlen(waitText) * 16;
            glRasterPos2i(WINDOW_WIDTH / 2 - waitTextWidth / 2, WINDOW_HEIGHT / 2);
            YsGlDrawFontBitmap16x24(waitText);
            if (state_timer > 2.0) {
                state = 19; // Move to the next state or end
                state_timer = 0.0;
            }
            break;
        }

        default:
            break;
        }

        DrawTimer(total_elapsed_seconds);
        FsSwapBuffers();
        FsSleep(16);

    //     // Play sound at specific events
    //     if (state == 0 && state_timer == 0.0) {
    //         player.PlayOneShot(soundData);
    //     }
    }

    // Clean up sound player before exiting
    player.Stop(song);
    player.End();
    return 0;
}
