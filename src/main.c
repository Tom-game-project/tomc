#include <stdio.h>
#include <unistd.h>
#include "test_tools.h"
#include "tokenizer.h"

int main()
{
	debug_dprintf(STDERR_FILENO, "hello\127  \"world\"\n");
	return (0);
}
