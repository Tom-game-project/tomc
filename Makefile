# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:33:31 by tmuranak          #+#    #+#              #
#    Updated: 2024/04/16 20:43:35 by tmuranak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cc = gcc
flag = -Wextra -Werror -Wall
src = ft_*.c
obj = ft_*.o

all:$(src)
	make createobj
	make createa

createobj: $(src)
	$(cc) $(flag) -c $(src)

createa: $(obj)
	ar -r libft.a $(obj)

clean:
	rm ft_*.o libft.a