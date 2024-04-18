#include <string.h>
#include <stdio.h>

void showmem(char *dst,int size)
{
    for (int i = 0; i < size;i++){
        if (dst[i])
        {
            printf("%c",dst[i]);
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}

int main ()
{
    // test00
    printf("--+ test00 +--\n");
    char dst00[6] = "hello\0";
    const char *src00 = "012345678\0";
    printf("dst:%s\nsrc:%s\n",dst00,src00);
    size_t r00 = strlcpy(dst00 , src00,sizeof(dst00));
    printf("dst result:%s\n",dst00);
    printf("return %zu\n",r00);
    showmem(dst00,6);
}
