# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 02:50:22 by gbabeau           #+#    #+#              #
#    Updated: 2020/10/20 17:31:55 by gbabeau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = srcs/ft_atoi.c srcs/ft_bzero.c srcs/ft_calloc.c srcs/ft_isalnum.c srcs/ft_isalpha.c srcs/ft_isascii.c srcs/ft_isdigit.c srcs/ft_isprint.c srcs/ft_itoa.c srcs/ft_memccpy.c srcs/ft_memchr.c srcs/ft_memcmp.c srcs/ft_memcpy.c srcs/ft_memmove.c srcs/ft_memset.c srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c srcs/ft_putstr_fd.c srcs/ft_split.c srcs/ft_strchr.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_strlcat.c srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_strmapi.c srcs/ft_strncmp.c srcs/ft_strnstr.c srcs/ft_strrchr.c srcs/ft_strtrim.c srcs/ft_substr.c srcs/ft_tolower.c srcs/ft_toupper.c srcs/ft_convert_base.c srcs/ft_convert_base2.c srcs/ft_convert_base_p.c srcs/ft_convert_base_p2.c srcs/ft_uitoa.c srcs/ft_ultoa.c srcs/ft_compare_c_to_s.c srcs/ft_logique.c
BO = srcs/ft_lstnew_bonus.c srcs/ft_lstadd_back_bonus.c srcs/ft_lstadd_front_bonus.c srcs/ft_lstclear_bonus.c srcs/ft_lstdelone_bonus.c srcs/ft_lstiter_bonus.c srcs/ft_lstlast_bonus.c srcs/ft_lstmap_bonus.c  srcs/ft_lstsize_bonus.c
BOFT = $(BO:.c=.o)
OBJ = $(SRCS:.c=.o)
HEAD = include
CFLAGS = -Wall -Werror -Wextra -I$(HEAD)
CC = gcc
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME)  $(OBJ)
bonus : $(OBJ) $(BOFT)
	ar rcs $(NAME) $(OBJ)  $(BOFT)
clean :
	rm -f $(OBJ) $(BOFT)
fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus  all clean fclean r e

