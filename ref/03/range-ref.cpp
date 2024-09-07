#include <stdio.h>

int main(void)
{
    int a[5]={1,2,3,4,5};
    for(auto &x : a)
    {
        x+=10;
    }
    for(auto x : a)
    {
        printf("%d\n",x);
    }
    return 0;
}
