#include "libft.h"
#include <stdbool.h>

bool ft_streq(char *str1, char *str2)
{
	size_t len;

	len = ft_strlen(str1);
	return len == ft_strlen(str2) && ft_strncmp(str1, str2, len) == 0;
}
