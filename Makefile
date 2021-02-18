# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 12:18:54 by tcordonn          #+#    #+#              #
#    Updated: 2021/02/18 12:49:12 by tcordonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEAD = -I./includes/ -I./libft/include

CFLAGS = #-Wall -Wextra -Werror

SRCS =  srcs/lexer/lexer.c \
		srcs/main.c \
		srcs/lexer/lexer2.c \
		srcs/lexer/quote.c \
		srcs/init.c \
		srcs/get_next_line.c \
		srcs/parser/init_struct_parser.c \
		srcs/parser/init_struct_pipe.c \
		srcs/parser/other.c \
		srcs/parser/parser_comand.c \
		srcs/parser/parser_input.c \
		srcs/parser/parser_output.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc -g $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft

G: $(OBJS)
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
