#include "test_tools.h"
#include <unistd.h>

int main()
{
	debug_dprintf(STDERR_FILENO, "%s\n", "hello world");
	return (0);
}
