/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:45 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 18:53:38 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void		*rbuf;
	size_t		buf_size;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	buf_size = count * size;
	rbuf = malloc(buf_size);
	if (rbuf == NULL)
		return (NULL);
	ft_bzero(rbuf, buf_size);
	return (rbuf);
}
