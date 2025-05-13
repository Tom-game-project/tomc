//#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int test00()
{
	int a = 0;
	int b = 0;
	int *a_ptr = &a;
	int *b_ptr = &b;
	int **a_ptr_ptr = &a_ptr;
	int **b_ptr_ptr = &b_ptr;

	assert(a == b);
	assert(*a_ptr == *b_ptr);
	assert(**a_ptr_ptr == **b_ptr_ptr);
	assert(a_ptr == &a);
	assert(a_ptr_ptr == &a_ptr);
	printf("%p \n", a_ptr);
	printf("%p \n", a_ptr_ptr);

	return (0);
}

int test01()
{
	char *str0 = "hello world";
	char *str1;
	char str2[] = "hello world";

	char str3[12]; // null文字を含める

	str1 = (char *)malloc(sizeof(char) * strlen(str0));
	strcpy(str3, str0);

	printf("`char *str0 = \"hello world\";` %p \n", str0);
	printf("`char *str1;` %p\n", str1);
	printf("`char str2[] = \"hello world\";` %p\n", str2);
	printf("`char str3[12];` %p\n", str3);

	return (0);
}

int test02()
{
	printf("%d \n", -   42);
	return (0);
}

/// ```
/// cc example_code.c -o example_code
/// ```
int main()
{
	test00();
	test01();
	test02();

	return (0);
}
