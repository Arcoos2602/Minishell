# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 10:33:28 by tcordonn          #+#    #+#              #
#    Updated: 2021/01/21 10:36:23 by tcordonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEAD = -I./includes/ -I./libft/include

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/test.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc -g $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft

clean:
	rm -rf $(OBJS) objs
	make clean -sC libft

fclean:
	make fclean -sC libft
	rm -rf $(NAME) $(OBJS)

re:	fclean
	make all

