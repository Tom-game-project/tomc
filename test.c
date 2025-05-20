#include <stdio.h>

struct ss_a{
};
struct ss_b{
};


struct s_a{
	enum {
		a,
		b
	} content_type;
	union {
		struct ss_a *a;
		struct ss_b *b;
	} inner_content;
};


int main()
{
	int a;

	a = 0;
	printf("%d", 1- --a);
	printf("%d", 1+ ++a);
	return (a);
}
