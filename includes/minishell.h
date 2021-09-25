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
# include "get_next_line.h"
# define BUFFER_SIZE 50000
# include "parser.h"
# include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int			g_global;

typedef struct	s_path
{
	char 		**path;
	char 		**exec_path;
	int			first[1];
	int     	start;
	int			exit;
	int			pipe_out;
	int 		pipe_in;
	int			starting;
	int 		dont;
	int 		exec;
	int			father;
	int			in_fd;
	int			out_fd;
	t_parser	*parser;
	int			exit_status;
}				t_path;

char			*ft_dol(char *str, int *i, t_path *path);
char			**tokenization(char *str, t_path *paths);
void			free_token(char	**token);
void			cpt2(char *str, int *i, int *cpt);
int				count_quote(char *str, int *i);
void			fill_quote(char **tab, char *str, int *i, int *x);
int				check_error(char *str, int *i , int *cpt);
int				token(char	c);
int				quote(char *str);
int				get_next_line(int fd, char **line);
int				init_inouput_back(char **lexer, char *inout);
int				ft_shell(t_parser *parser, t_path *path);
void			display_total(t_parser *parser);
int				display_error_token(char c);
int				ft_pipe(t_pipes *pipes, t_path *path, pid_t *pid_2);
void			ft_free_redi(t_redi *redi);
void			ft_free(t_parser *parser, t_path *path);
int				redirect_out(char *put, t_redi *redi, int *pipe_out);
int				redirect_in(char *command, char *put, t_redi *redi, int *pipe_in);
void 			free_paths(t_path *path);
pid_t			father_0(t_pipes *pipes, t_path *path, int buf[2]);
void			child(t_pipes *pipes, t_path *path, pid_t *pid_2);
void			ft_free_pipe(t_pipes *pipe);
void			ft_free_paths(char **paths);
void			ft_close(int pipe_1, int pipe_2, int pipe_3, int pipe_4);
int				exit_ft_pipe(pid_t pid, t_pipes *pipes, t_path *path);
int				init_redi(t_pipes *pipes, int buf[2]);
int				init_fd(t_pipes *pipes, int buf[2], int pipe_fd[2], t_path *path);
int				exit_ft_parser(pid_t pid, t_parser *parser, t_path *path);
int				get_next_line(int fd, char **line);
int				check_builtins(t_pipes	*pipes, t_path *path, char **env);
void			ft_exit(t_path *path, t_pipes *pipes);
t_pipes			*init_pipes(char **lexer, int *i, t_path *paths);
t_parser		*init_parser(char **lexer, int *i, t_path *paths);
t_parser		*parser_new(char **lexer, int *i, t_path *paths);
t_pipes			*pipe_new(char **lexer, int *i, t_path *paths);
t_pipes			*init_new(t_pipes *t_new, char **lexer, int *i, t_path *path);
char			**init_command_pipe(char **command, char **lexer, int *i, t_path *paths);
t_redi			*init_put(t_redi *t_new, char **lexer, int *i, t_path *paths);
char			*parse(char *str, t_path *path);

#endif
