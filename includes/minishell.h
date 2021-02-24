#ifndef MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# define BUFFER_SIZE 1096
# include "../libft/include/libft.h"
# include "parser.h"

typedef struct	s_main
{
	char	*line;
	char	**lexer;
	int		command_nbr;
}				t_main;

typedef struct	s_bi_parser
{
	char					*command;
	struct	s_bi_parser		*left;
	struct	s_bi_parser		*rigth;
}				t_bi_parser;

int				lexer(t_main *vars);
int				init_all(t_main	*vars);
int				not_handled(char *str);
char			**token(char *str);
void			cpt2(char *str, int *i, int *cpt);
void			count_quote(char *str, int *i, int *cpt);
void			fill_quote(char **tab, char *str, int *i, int *x);
int				check_multi(char *str);
int				check_char(char c);
int				separators(char	c);
int				quote(char *str);
int				get_next_line(int fd, char **line);
int				init_inouput_back(char **lexer, char *inout);
#endif
