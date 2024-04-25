#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int main ()
{
	char *dst1 = calloc(100, sizeof(char));
	char *dst2 = calloc(100, sizeof(char));
	char *src1 = calloc(100, sizeof(char));
	char *src2 = calloc(100, sizeof(char));
	for (int i = 0; i < 99; i++)
	{
		src1[i] = i + 1;
		src2[i] = i + 1;
	}
    printf("%lu %lu,\n",ft_strlcat(dst1, src1, 100), strlcat(dst2, src2, 100));
}