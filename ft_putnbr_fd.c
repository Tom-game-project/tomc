/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:04:28 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 16:26:30 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <unistd.h>
#include <limits.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_recursive(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_recursive(n / 10, fd);
	ft_putchar('0' + n % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	n = (long int)n;
	if (n == -2147483648)
		write(fd, &"-2147483648", 11);
	else
		ft_putnbr_recursive(n, fd);
}
