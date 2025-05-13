#include <stdio.h>

int main()
{
	int a;

	a = 0;
	printf("%d", 1- --a);
	printf("%d", 1+ ++a);
	return (a);
}
