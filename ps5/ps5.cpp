#include "fssimplewindow.h"
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WALL_THICKNESS = 10;

int main(void)
{
	double circleX = 400, circleY = 300, circleSize = 20;
	int currentColor = 0, previousColor = 0;

	FsOpenWindow(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,1);
	glShadeModel(GL_SMOOTH); 

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		// Interactive movement
		if (FsGetKeyState(FSKEY_LEFT))  circleX -= 5;
		if (FsGetKeyState(FSKEY_RIGHT)) circleX += 5;
		if (FsGetKeyState(FSKEY_UP))    circleY -= 5;
		if (FsGetKeyState(FSKEY_DOWN))  circleY += 5;

		// Wall collision detection and color change
		if (circleX - circleSize <= WALL_THICKNESS) {
			circleX = WALL_THICKNESS + circleSize;
			previousColor = currentColor;
			currentColor = 0; // Red
		}
		if (circleX + circleSize >= WINDOW_WIDTH - WALL_THICKNESS) {
			circleX = WINDOW_WIDTH - WALL_THICKNESS - circleSize;
			previousColor = currentColor;
			currentColor = 2; // Green
		}
		if (circleY - circleSize <= WALL_THICKNESS) {
			circleY = WALL_THICKNESS + circleSize;
			previousColor = currentColor;
			currentColor = 1; // Blue
		}
		if (circleY + circleSize >= WINDOW_HEIGHT - WALL_THICKNESS) {
			circleY = WINDOW_HEIGHT - WALL_THICKNESS - circleSize;
			previousColor = currentColor;
			currentColor = 3; // Yellow
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		// Draw walls
		glBegin(GL_QUADS);
		glColor3ub(255,0,0);  // Red
		glVertex2i(0, 0);
		glVertex2i(WALL_THICKNESS, 0);
		glVertex2i(WALL_THICKNESS, WINDOW_HEIGHT);
		glVertex2i(0, WINDOW_HEIGHT);
		glColor3ub(0,0,255);  // Blue
		glVertex2i(0, 0);
		glVertex2i(WINDOW_WIDTH, 0);
		glVertex2i(WINDOW_WIDTH, WALL_THICKNESS);
		glVertex2i(0, WALL_THICKNESS);
		glColor3ub(0,255,0);  // Green
		glVertex2i(WINDOW_WIDTH - WALL_THICKNESS, 0);
		glVertex2i(WINDOW_WIDTH, 0);
		glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
		glVertex2i(WINDOW_WIDTH - WALL_THICKNESS, WINDOW_HEIGHT);
		glColor3ub(255,255,0);  // Yellow
		glVertex2i(0, WINDOW_HEIGHT - WALL_THICKNESS);
		glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT - WALL_THICKNESS);
		glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
		glVertex2i(0, WINDOW_HEIGHT);
		glEnd();

		// Draw player circle with color gradient
		glBegin(GL_TRIANGLE_FAN);
		switch(previousColor) {
			case 0: glColor3ub(255,0,0); break; // Red
			case 1: glColor3ub(0,0,255); break; // Blue
			case 2: glColor3ub(0,255,0); break; // Green
			case 3: glColor3ub(255,255,0); break; // Yellow
		}
		glVertex2d(circleX, circleY - circleSize);
		switch(currentColor) {
			case 0: glColor3ub(255,0,0); break; // Red
			case 1: glColor3ub(0,0,255); break; // Blue
			case 2: glColor3ub(0,255,0); break; // Green
			case 3: glColor3ub(255,255,0); break; // Yellow
		}
		glVertex2d(circleX, circleY + circleSize);
		for (int i = 0; i <= 32; ++i)
		{
			double angle = (double)i * 3.14159 * 2.0 / 32.0;
			double x = circleX + cos(angle) * circleSize;
			double y = circleY + sin(angle) * circleSize;
			if (y < circleY) {
				switch(previousColor) {
					case 0: glColor3ub(255,0,0); break; // Red
					case 1: glColor3ub(0,0,255); break; // Blue
					case 2: glColor3ub(0,255,0); break; // Green
					case 3: glColor3ub(255,255,0); break; // Yellow
				}
			} else {
				switch(currentColor) {
					case 0: glColor3ub(255,0,0); break; // Red
					case 1: glColor3ub(0,0,255); break; // Blue
					case 2: glColor3ub(0,255,0); break; // Green
					case 3: glColor3ub(255,255,0); break; // Yellow
				}
			}
			glVertex2d(x, y);
		}
		glEnd();

		FsSwapBuffers();
	}
}