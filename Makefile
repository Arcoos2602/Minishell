NAME = minishell
HEAD = -I./includes/ -I./libft/include

CFLAGS = -Wall -Werror -Wextra #-lreadline

SRCS =  srcs/lexer/lexer.c \
		srcs/main.c \
		srcs/lexer/lexer2.c \
		srcs/lexer/quote.c \
		srcs/lexer/free_lexer.c \
		srcs/lexer/error.c \
		srcs/pipes.c \
		srcs/parser/init_struct_parser.c \
		srcs/parser/init_struct_pipe.c \
		srcs/parser/init_struct_pipe2.c \
		srcs/parser/init_struct_pipe3.c \
		srcs/parser/other.c \
		srcs/parser/parser_command.c \
		srcs/parser/parser_command2.c \
		srcs/parser/parser_command3.c \
		srcs/builtins/builtins.c \
		srcs/builtins/env.c \
		srcs/builtins/export2.c \
		srcs/builtins/pwd.c \
		srcs/builtins/echo.c \
		srcs/builtins/unset.c \
		srcs/builtins/export.c \
		srcs/builtins/exit.c \
		srcs/builtins/exit2.c \
		srcs/builtins/cd.c \
		srcs/parser/free_parser.c \
		srcs/father.c \
		srcs/father_exec.c \
		srcs/child.c \
		srcs/var_env.c \
		srcs/var_env2.c \
		srcs/signal.c \
		srcs/free_general.c \
		srcs/redirect.c \
		srcs/get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	clang -g $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft

G: $(OBJS)
	make -C ./libft
	clang -g3 -fsanitize=address $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft

clean:
	rm -rf $(OBJS) objs
	make clean -sC libft

fclean:
	make fclean -sC libft
	rm -rf $(NAME) $(OBJS)

re:	fclean
	make all
