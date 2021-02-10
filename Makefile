# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 10:33:28 by tcordonn          #+#    #+#              #
#    Updated: 2021/02/10 13:59:00 by tcordonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEAD = -I./includes/ -I./libft/include

CFLAGS = -Wall -Wextra -Werror

SRCS =  srcs/lexer2.c \
		srcs/init.c \
		srcs/get_next_line.c \
		srcs/lexer.c \
		#srcs/parser.c \
		srcs/utils.c \
		srcs/exec.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc -g3 -fsanitize=address $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft

clean:
	rm -rf $(OBJS) objs
	make clean -sC libft

fclean:
	make fclean -sC libft
	rm -rf $(NAME) $(OBJS)

re:	fclean
	make all

