# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:33:31 by tmuranak          #+#    #+#              #
#    Updated: 2024/05/01 15:09:45 by tmuranak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wextra -Werror -Wall
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBJ = $(SRC:.c=.o)
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
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
