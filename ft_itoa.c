/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:29:33 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/22 18:44:07 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void	ft_putnbr_recursive(int n, int *count)
{
	if (n < 0)
	{
		(*count)++;
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_recursive(n / 10, count);
	(*count)++;
}

static int	ft_intstrlength(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		return (11);
	else
		ft_putnbr_recursive(nb, &count);
	return (count);
}

static int	pow10(int a)
{
	int	rint;
	int	i;

	rint = 1;
	i = 0;
	while (i < a)
	{
		rint *= 10;
		i++;
	}
	return (rint);
}

char	*ft_itoa(int n)
{
	char	*rbuf;
	int		i;
	int		length;

	length = ft_intstrlength(n);
	rbuf = malloc(sizeof(char) * (length + 1));
	i = 0;
	if (n < 0)
	{
		rbuf[i] = '-';
		i++;
		if (n == -2147483648)
			return (ft_memcpy(rbuf, "-2147483648", \
			sizeof(char) * (length + 1)));
		n *= -1;
	}
	while (i < length)
	{
		rbuf[i] = (n / pow10((length - i) - 1)) + '0';
		n -= (n / pow10(length - i - 1)) * pow10(length - i - 1);
		i++;
	}
	rbuf[i] = '\0';
	return (rbuf);
}
