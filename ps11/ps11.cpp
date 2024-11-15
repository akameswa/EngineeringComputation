#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

const double PI = 3.14159265359;

struct Point {
    double x, y;
    Point(double x_=0, double y_=0) : x(x_), y(y_) {}
};

class CrankSimulation {
private:
    const double L1 = 1.0;
    const double L2 = 4.0;
    const double L3 = 2.0;
    const double L = 4.0;
    const int SCALE = 100;
    const int ORIGIN_X = 100;
    const int ORIGIN_Y = 500;

    static const int NUM_SAMPLES = 60;
    Point pathPoints[NUM_SAMPLES];
    double angle = 0.0;

public:
    void calculatePoints(double theta, Point &p1, Point &p2, Point &p3) {
        p1.x = L1 * cos(theta);
        p1.y = L1 * sin(theta);
        p3.x = L;
        p3.y = 0;
        double d = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));
        if (d > L2 + L3 || d < fabs(L2 - L3)) {
            return;
        }
        double a = (L2*L2 - L3*L3 + d*d) / (2*d);
        double h = sqrt(L2*L2 - a*a);
        double x2 = p1.x + a*(p3.x - p1.x)/d;
        double y2 = p1.y + a*(p3.y - p1.y)/d;
        double x2_part = h*(p3.y - p1.y)/d;
        double y2_part = h*(p3.x - p1.x)/d;
        double p2a_x = x2 + x2_part;
        double p2a_y = y2 - y2_part;
        double p2b_x = x2 - x2_part;
        double p2b_y = y2 + y2_part;
        if (p2a_y > p2b_y) {
            p2.x = p2a_x;
            p2.y = p2a_y;
        } else {
            p2.x = p2b_x;
            p2.y = p2b_y;
        }
    }
    
    void generatePaths() {
        for(int i = 0; i < NUM_SAMPLES; ++i) {
            double theta = 2.0 * PI * i / NUM_SAMPLES;
            Point p1, p2, p3;
            calculatePoints(theta, p1, p2, p3);
            pathPoints[i].x = (p1.x + p2.x) / 2.0;
            pathPoints[i].y = (p1.y + p2.y) / 2.0;
        }
    }
    
    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        Point p1, p2, p3;
        calculatePoints(angle, p1, p2, p3);
        glColor3ub(128, 128, 128);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < NUM_SAMPLES; ++i) {
            glVertex2d(ORIGIN_X + pathPoints[i].x * SCALE, 
                       ORIGIN_Y - pathPoints[i].y * SCALE);
        }
        glEnd();
        glColor3ub(255, 0, 0);
        glBegin(GL_LINES);
        glVertex2d(ORIGIN_X, ORIGIN_Y);
        glVertex2d(ORIGIN_X + p1.x * SCALE, ORIGIN_Y - p1.y * SCALE);
        glVertex2d(ORIGIN_X + p1.x * SCALE, ORIGIN_Y - p1.y * SCALE);
        glVertex2d(ORIGIN_X + p2.x * SCALE, ORIGIN_Y - p2.y * SCALE);
        glVertex2d(ORIGIN_X + p2.x * SCALE, ORIGIN_Y - p2.y * SCALE);
        glVertex2d(ORIGIN_X + p3.x * SCALE, ORIGIN_Y - p3.y * SCALE);
        glEnd();
        glColor3ub(0, 0, 0);
        drawTriangle(ORIGIN_X, ORIGIN_Y, 10);
        drawTriangle(ORIGIN_X + p3.x * SCALE, ORIGIN_Y - p3.y * SCALE, 10);
        glColor3ub(0, 255, 0);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex2d(ORIGIN_X + p1.x * SCALE, ORIGIN_Y - p1.y * SCALE);
        glVertex2d(ORIGIN_X + p2.x * SCALE, ORIGIN_Y - p2.y * SCALE);
        glVertex2d(ORIGIN_X + (p1.x + p2.x)/2 * SCALE, ORIGIN_Y - (p1.y + p2.y)/2 * SCALE);
        glEnd();
        drawText("P0", ORIGIN_X - 20, ORIGIN_Y + 20);
        drawText("P1", ORIGIN_X + p1.x * SCALE - 20, ORIGIN_Y - p1.y * SCALE + 20);
        drawText("P2", ORIGIN_X + p2.x * SCALE - 20, ORIGIN_Y - p2.y * SCALE + 20);
        drawText("P3", ORIGIN_X + p3.x * SCALE - 20, ORIGIN_Y - p3.y * SCALE + 20);
    }
    
    void update() {
        angle += 0.01;
        if(angle > 2.0 * PI) {
            angle -= 2.0 * PI;
        }
    }

    void drawTriangle(double x, double y, double size) {
        glBegin(GL_TRIANGLES);
        glVertex2d(x, y - size);
        glVertex2d(x - size, y + size);
        glVertex2d(x + size, y + size);
        glEnd();
    }
    
    void drawText(const char* str, double x, double y) {
        glRasterPos2d(x, y);
        glColor3ub(0, 0, 0);
        YsGlDrawFontBitmap8x12(str);
    }
};

int main(void) {
    FsOpenWindow(0, 0, 800, 600, 1);
    CrankSimulation sim;
    sim.generatePaths();
    while(FsInkey() != FSKEY_ESC) {
        sim.draw();
        sim.update();
        FsSwapBuffers();
        FsSleep(10);
    }
    return 0;
}