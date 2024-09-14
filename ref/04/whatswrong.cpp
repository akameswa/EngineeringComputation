// This can be tested on Windows only.

#include <stdio.h>
#include <windows.h>

#undef rad1

int main(void)
{
    double rad1=1.0;
    // In VS2015, also "environ" gives something interesting.
    printf("rad1=%lf\n",rad1);
    return 0;
}
