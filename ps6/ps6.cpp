#include <iostream>
#include <cmath>
#include "fssimplewindow.h"

const double tolerance = 1e-6;

class Equation {
public:
    double a, b, c;

    void Plot(float R, float G, float B) {
        glColor3f(R, G, B);
        glBegin(GL_LINE_STRIP);
        for (int x = -300; x <= 300; x++) {
            double worldX = x / 10.0;  
            double worldY = (c - a * worldX ) / (b + tolerance);
            glVertex2d(x + 300, 300 - worldY * 10);
        }
        glEnd();
    }
};

class SimultaneousEquation {
public:
    Equation eqn[2];

    bool Solve(double &x, double &y) {
        double a = eqn[0].a, b = eqn[0].b, c = eqn[0].c;
        double d = eqn[1].a, e = eqn[1].b, f = eqn[1].c;

        double det = std::abs((a * e) - (b * d));
        if (det < tolerance)
        {
            return false;
        }
        else
        {
            x = ((e * c) - (b * f)) / det;
            y = ((a * f) - (c * d)) / det;
            return true;
        }
    }

    void Plot() {
        eqn[0].Plot(1, 0, 0); // Red
        eqn[1].Plot(0, 0, 1); // Blue
    }
};

class Axes {
public:
    void Draw() {
        glColor3f(0.7f, 0.7f, 0.7f);
        glBegin(GL_LINES);
        for (int i = 0; i <= 600; i += 20) {
            glVertex2i(i, 0);
            glVertex2i(i, 600);
            glVertex2i(0, i);
            glVertex2i(600, i);
        }
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(300, 0);
        glVertex2i(300, 600);
        glVertex2i(0, 300);
        glVertex2i(600, 300);
        glEnd();
    }
};

int main(void)
{
    SimultaneousEquation eqn;
    Axes axes;
    double x, y;
    std::cout << "ax+by=c\n";
    std::cout << "dx+ey=f\n";
    std::cout << "Enter a b c d e f:";
    std::cin >>
        eqn.eqn[0].a >> eqn.eqn[0].b >> eqn.eqn[0].c >>
        eqn.eqn[1].a >> eqn.eqn[1].b >> eqn.eqn[1].c;

    if (eqn.Solve(x, y))
    {
        std::cout << "x=" << x << " y=" << y << '\n';
    }
    else
    {
        std::cout << "No solution.\n";
    }

    FsOpenWindow(0, 0, 600, 600, 1);

    for (;;)
    {
        FsPollDevice();
        if (FSKEY_ESC == FsInkey())
        {
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        axes.Draw();
        eqn.Plot();

        FsSwapBuffers();
    }
    return 0;
}