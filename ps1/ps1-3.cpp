#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main()
{
    int a, b, c, d, e, f;
    printf("ax + by = c \ndx + ey = f \nEnter a b c d e f:");
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

    double det = std::abs((a * e) - (b * d));
    if (det < 0.000001)
    {
        printf("No Solution");
    }
    else
    {
        double x = ((e * c) - (b * f)) / det;
        double y = ((a * f) - (c * d)) / det;
        printf("x=%f y=%f", x, y);
    }

    return 0;
}