/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:08:20 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 18:02:13 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	atoi_helper(char *str, int len)
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

static char	*prefix_helper(char *str, int *flag)
{
	*flag = 1;
	while (!ft_isdigit(*str))
	{
		if (*str == '-')
		{
			*flag = -1;
			str++;
			break ;
		}
		if (*str == '+')
			break ;
		if (!isspace(*str))
			return (0);
		str++;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int				flag;
	int				len;
	char			*strtmp;

	len = 0;
	strtmp = (char *)str;
	strtmp = prefix_helper(strtmp, &flag);
	while (ft_isdigit(*strtmp))
	{
		len++;
		strtmp++;
	}
	return (flag * atoi_helper(strtmp - len, len));
}
