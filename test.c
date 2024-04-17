
#include "libft.h"

void	ft_bzero(void *s, size_t n);

int main ()
{
    
    char buf[5] = "hello";
    ft_bzero(buf,5);
    for (int i = 0;i < 5;i++)
    {
        if (buf[i]){
            printf("True");
        }else{
            printf("False");
        }
    }

    char str1[128] = {1,1,1,1,1,1,1};
    char str2[] = "ab\0cde";        /* 途中に空文字のある文字列 */
    int i;
    
    printf("コピー前　中身の確認\n");
    for (i=0; i<7; i++)
            printf("%#x ",str1[i]);
    printf("\n");
    
    ft_memcpy(str1, str2, 5);
    printf("コピー後　中身の確認\n");
    for (i=0; i<7; i++)
            printf("%#x ",str1[i]);
    printf("\n");
    return 0;
}