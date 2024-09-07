#include <stdio.h>

void SwapInt(int a[2])
{
    int c;
    c=a[0];
    a[0]=a[1];
    a[1]=c;
}

int main(void)
{
    int n[2];
    n[0]=1;
    n[1]=2;
    printf("Before: n[0]=%d n[1]=%d\n",n[0],n[1]);
    SwapInt(n);
    printf("After:  n[0]=%d n[1]=%d\n",n[0],n[1]);
    return 0;
}

