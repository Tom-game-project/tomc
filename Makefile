# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:33:31 by tmuranak          #+#    #+#              #
#    Updated: 2024/04/30 21:38:55 by tmuranak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wextra -Werror -Wall
SRC = $(filter-out $(wildcard ft_lst*.c),$(wildcard ft_*.c))
OBJ = $(SRC:.c=.o)
BONUS = $(wildcard ft_lst*.c)
BONUSOBJ = $(BONUS:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME):$(OBJ) $(BONUSOBJ)
	ar -r $(NAME) $(OBJ) $(BONUSOBJ)

bonus:$(BONUSOBJ)
	ar -r $(NAME) $(BONUSOBJ)

%.o: %.c
	$(CC) $(CFLAG) -c $<

clean:
	rm ft_*.o

fclean: clean
	rm libft.a

re: fclean
	make
