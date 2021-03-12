NAME = minishell
HEAD = -I./includes/ -I./libft/include

CFLAGS = #

SRCS =  srcs/lexer/lexer.c \
		srcs/main.c \
		srcs/lexer/lexer2.c \
		srcs/lexer/quote.c \
		srcs/pipes.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/parser/init_struct_parser.c \
		srcs/parser/init_struct_pipe.c \
		srcs/parser/other.c \
		srcs/parser/parser_comand.c \
		srcs/parser/parser_input.c \
		srcs/parser/parser_output.c \
		srcs/builtins/builtins.c \
		srcs/builtins/env.c

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
