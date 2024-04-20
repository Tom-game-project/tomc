/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:45 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 18:38:04 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rbuf;
	size_t	buf_size;

	buf_size = count * size;
	rbuf = malloc(buf_size);
	if (!rbuf)
		return (NULL);
	ft_memset(rbuf, 0, buf_size);
	return (rbuf);
}
