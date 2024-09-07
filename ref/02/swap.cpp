#include <stdio.h>

void SwapInt(int &a,int &b)
{
    int c;
    c=b;
    b=a;
    a=c;
}
int main(void)
{
    int a,b;
    a=1;
    b=2;
    printf("Before: a=%d b=%d\n",a,b);
    SwapInt(a,b);
    printf("After:  a=%d b=%d\n",a,b);
    return 0;
}
