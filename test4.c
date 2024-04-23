#include "libft.h"
#include <stdio.h>


void helper29(unsigned int i, char *c)
{
    // test29
    if ('a' <= *c && *c <= 'z')
    {
        printf("T %d %c %p\n",i,*c,c);
        //*c = (*c - ('a' - 'A'));
        *c = '*';
    }else
    {
        printf("F %d %c %p\n",i,*c,c);
    }
}

int main()
{
    char a = 'a';

    helper29(0,&a);
    printf("%c\n",a);
}