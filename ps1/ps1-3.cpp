#include <iostream>

int main()
{
    int a, b, c, d, e, f;
    printf("ax + by = c \ndx + ey = f \nEnter a b c d e f:");
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

    float abs_val = ((a * e) - (b * d));
    if (abs_val < 0.000001)
    {
        printf("No Solution");
    }
    else
    {
        int x = ((e * c) - (b * f)) / abs_val;
        int y = ((a * f) - (c * d)) / abs_val;
        printf("x=%d y=%d", x, y);
    }

}

