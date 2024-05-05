/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:37:46 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 18:35:09 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	isspace(int c)
{
	return (
		c == '\t' || \
		c == '\n' || \
		c == '\v' || \
		c == '\f' || \
		c == '\r' || \
		c == ' '
	);
}

static char	*atoi_helper1(const char *str, int *flag)
{
	char	*strtmp;

	*flag = 1;
	strtmp = (char *)str;
	while (!ft_isdigit(*strtmp))
	{
		if (*strtmp == '-')
		{
			*flag = -1;
			strtmp++;
			break ;
		}
		else if (*strtmp == '+')
		{
			strtmp++;
			break ;
		}
		else if (!isspace(*strtmp))
		{
			*flag = 0;
			break ;
		}
		strtmp++;
	}
	return (strtmp);
}

static int	overflow_checker(unsigned long int num, char next_c, int flag)
{
	if ((LONG_MAX / 10 <= num) && (7 < next_c - '0') && flag == 1)
	{
		return (-1);
	}
	else if ((LONG_MAX / 10 <= num) && (8 <= next_c - '0') && flag == -1)
	{
		return (1);
	}
	else if (1000000000000000000 <= num)
	{
		return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int		num;
	int						flag;
	char					*strtmp;
	int						c;

	num = 0;
	strtmp = atoi_helper1(str, &flag);
	c = 0;
	while (*strtmp && ft_isdigit(*strtmp))
	{
		if (overflow_checker(num, *strtmp, flag) == -1)
			return (-1);
		else if (overflow_checker(num, *strtmp, flag) == 1)
			return (0);
		num = num * 10 + (unsigned long)(*strtmp - '0');
		strtmp++;
		c++;
	}
	return (flag * num);
}
