#include "libft.h"
#include <stdio.h>
//#include <string.h>

int main()
{
	char dst[100];
	//ft_strlcpy(dst,"hello        \n",5);
	strlcpy(dst,"   hello    ",6);
	printf("%s\n",dst);
}