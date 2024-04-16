
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
}