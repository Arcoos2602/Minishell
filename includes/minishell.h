#ifndef MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# define BUFFER_SIZE 50000
# include "parser.h"
# include "get_next_line.h"
# include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int			global;

typedef struct	s_path
{
	char 		**path;
	char 		**exec_path;
	int			first[1];
  int     start;
  int     exit;
	int			pipe_out;
	int 		pipe_in;
  int     exit_status;
}				t_path;

int				not_handled(char *str);
char			**tokenization(char *str, char **path);
void			free_token(char	**token);
void			cpt2(char *str, int *i, int *cpt);
void			count_quote(char *str, int *i, int *cpt);
void			fill_quote(char **tab, char *str, int *i, int *x);
int				check_multi(char *str);
int				check_char(char c);
int				separators(char	c);
int				quote(char *str);
int				get_next_line(int fd, char **line);
int				init_inouput_back(char **lexer, char *inout);
int				ft_shell(t_parser *parser, t_path path);
void			display_total(t_parser *parser);
int				ft_pipe(t_pipes *pipe, t_pipes *pipes, t_path *path, pid_t *pid_2);
void			ft_free_redi(t_redi *redi);
void			ft_free(t_pipes *pipe, t_path *path);
int				redirect_out(char *put, t_redi *redi, int *pipe_out);
int				redirect_in(char *command, char *put, t_redi *redi, int *pipe_in);
void 		free_paths(t_path *path);

#endif
