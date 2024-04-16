# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:33:31 by tmuranak          #+#    #+#              #
#    Updated: 2024/04/16 23:33:51 by tmuranak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wextra -Werror -Wall
SRC = ft_*.c
OBJ = ft_*.o
NAME = libft.a

all: $(NAME)

$(NAME):create
	ar -r $(NAME) $(OBJ)

create: $(OBJ)
	$(CC) $(CFLAG) -c $(SRC)

clean:
	rm ft_*.o

fclean:clean
	rm libft.a

re:
	make fclean
	make