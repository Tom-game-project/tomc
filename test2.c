
#include <stdio.h>

void changeint(char *a)
{
	*a = 'b';
}

int	main ()
{
	char a = 'a';

	changeint(&a);
	printf("%c\n",a);
	return (0);
}