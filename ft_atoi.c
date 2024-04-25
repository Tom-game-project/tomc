/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:37:46 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/25 18:59:32 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	isspace(int c)
{
	if (
		c == '\t' || \
		c == '\n' || \
		c == '\v' || \
		c == '\f' || \
		c == '\r' || \
		c == ' '
	)
		return (1);
	return (0);
}

static int    atoi_helper(char *str, int len)
{
	int	c;
	int	i;
	int	base;
	int	r;

	c = len;
	r = 0;
	while (0 < c--)
	{
		i = 0;
		base = 1;
		while (i < (len - c - 1))
		{
			i++;
			base *= 10;
		}
		r += (str[c] - '0') * base;
    }
    return (r);
}

static int    prefix_helper(char *str)
{
    while (!ft_isdigit(*str))
    {
        if (*str == '-')
        {
            str++;
            return (-1);
        }
        else if (*str == '+')
        {
            str++;
            return (1);
        }
        else if (isspace(*str))
            str++;
        else
            return (0);
    }
    return (1);
}

int    ft_atoi(const char *str)
{
	int		flag;
	int		len;
	char	*strtmp;
	int		count;

	count = 0;
	len = 0;
	strtmp = (char *)str;
	if (!*str)
		return (0);
	flag = prefix_helper(strtmp);
	while (!(ft_isdigit(*strtmp)))
		strtmp++;
	while (ft_isdigit(*strtmp))
	{
		len++;
		strtmp++;
		count++;
	}
	while (count)
	{
		strtmp--;
		count--;
	}
    printf("%d\n",flag * atoi_helper(strtmp, len));
    return (flag * atoi_helper(strtmp, len));
}

// int main()
// {
//     char *a = "-1";
//     printf("%d",ft_atoi2(a));
// }