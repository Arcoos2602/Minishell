/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:02:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/10/04 15:38:37 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <readline/readline.h>
# include <readline/history.h>

# define ENV "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_012345678910"

extern int			g_global;

typedef struct s_path
{
	char		**path;
	char		**exec_path;
	int			first[1];
	int			start;
	int			exit;
	int			pipe_out;
	int			pipe_in;
	int			starting;
	int			dont;
	int			exec;
	int			father;
	int			in_fd;
	int			out_fd;
	t_parser	*parser;
	int			exit_status;
	int			buffer_fd[2];
}				t_path;

int				elem(char *str, int *cpt, int *i);
int				cpt(char *str);
char			*ft_dol(char *str, int *i, t_path *path);
char			**tokenization(char *str, t_path *paths);
void			free_token(char	**token);
int				count_quote(char *str, int *i);
int				check_error(char *str, int *i, int *cpt);
int				token(char c);
int				ft_free_redi_double(t_redi *redi, t_path *path);
char			**comand_malloc_2(char **command, t_path *paths, int size);
char			**split_command(char **command, int *size);
char			**comand_malloc(char **command, char **lexer);
char			**command_trad(char **command, t_path *paths, int size);
char			**command_split_2(char **dest, char **command, int *i, int *d);
char			*command_trad_2(char *command, t_path *paths);
int				count_tab(char **command);
int				quote(char *str);
int				ft_shell(t_parser *parser, t_path *path);
int				display_error_token(char c);
int				ft_pipe(t_pipes *pipes, t_path *path, pid_t *pid_2);
void			ft_free_redi(t_redi *redi);
void			ft_free(t_parser *parser, t_path *path);
int				redirect_out(int *put, t_redi *redi, int *pipe_out);
int				redirect_in(t_path *path, int *put,
					t_redi *redi, int *pipe_in);
void			free_paths(t_path *path);
pid_t			father_0(t_pipes *pipes, t_path *path, int buf[2]);
int				ft_execve(char *s1, char *s2, char **command, char **env);
void			ft_excve_2(t_pipes *pipes, t_path *path);
void			command_not_found(t_pipes *pipes, t_path *path);
void			child(t_pipes *pipes, t_path *path, pid_t *pid_2);
void			ft_free_pipe(t_pipes *pipe);
void			ft_free_paths(char **paths);
void			ft_close(int pipe_1, int pipe_2, int pipe_3, int pipe_4);
int				exit_ft_pipe(pid_t pid, t_pipes *pipes, t_path *path);
int				init_redi(t_path *path, t_pipes *pipes, int buf[2]);
int				init_fd(t_pipes *pipes, int buf[2],
					int pipe_fd[2], t_path *path);
int				get_next_line(char **line, int i);
int				check_builtins(t_pipes	*pipes, t_path *path, char **env);
void			ft_exit(t_path *path, t_pipes *pipes);
t_pipes			*init_pipes(char **lexer, int *i, t_path *paths);
t_parser		*init_parser(char **lexer, t_path *paths);
char			*add_newline(char *line, t_path *path);
char			*ft_replace(char *line, t_path *path);
char			*ft_buff_no_null(char *line, int cpt, int i, char *buff);
char			*ft_buff_null(char *line, int cpt, int i);
t_redi			*init_put(t_redi *redi, char **lexer, int *i, t_path *paths);
t_redi			*add_redi(t_redi *redi, t_redi *next);
t_redi			*redi_new(char **lexer, t_path *paths);
t_redi			*init_new_redi(t_redi *redi, char **lexer, t_path *paths);
int				ft_free_redi_double(t_redi *redi, t_path *path);
int				nbr_redi(char **lexer);
t_parser		*parser_new(char **lexer, int *i, t_path *paths);
char			*parse(char *str, t_path *path);
char			*parse_put(char *str, t_path *path);
t_pipes			*pipe_new(char **lexer, int *i, t_path *paths);
t_pipes			*init_new(t_pipes *t_new, char **lexer, int *i, t_path *path);
char			**init_command_pipe(char **command,
					char **lexer, int *i, t_path *paths);
t_redi			*init_put(t_redi *t_new, char **lexer, int *i, t_path *paths);
char			**ft_export(t_pipes *pipes, char **env, t_path *path);
void			set_j(char **env, int *x, int *j);
int				ft_count(char *str, int *i, char *test);
void			ft_dup_redi(t_pipes *pipes, int buf[2]);
void			ambigous(t_redi *redi, char **lexer, t_path*paths);
char			*double_quotes(char *str, int *i, t_path *path);
void			ft_env(char **path);
void			ft_pwd(void);
char			**env_malloc(char **path, char **env);
void			ft_echo(t_pipes *pipes);
void			ft_cd(t_pipes *pipes, char **env);
char			**ft_unset(t_pipes *pipes, char **env, t_path *path);
char			*ft_getenv(char **paths, char *var);
void			ft_signal(int n);
char			**new_env_exp(char **env, char *to_add, int size);
void			ft_print_env_alp(char **env);
int				is_valid(char *str);
char			*parse_4(int *i, char *str, char *dest, t_path *path);
int				ft_open_here_doc(t_redi *re, t_path *pat, int *pipe_in, int *p);
int				file_error(char *str);
char			*dup_rediput(char *lexer);
int				ft_count_dol(char *str, int *i, char *test);
int				ft_size_arg_add(char *str);
void			init_ft_pipe(t_pipes *pipes, int buf[2]);
void			init_path_shell(t_path *path);
#endif
