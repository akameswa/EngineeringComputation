#include <stdio.h>
#include <string.h>
int main(void)
{
    char s[256];
    strncpy(s,"1234567890",255);
    strncpy(s,"ABCDE",5);
	s[5]=0;
    printf("%s\n",s);
    return 0;
}
