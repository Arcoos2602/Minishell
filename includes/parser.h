/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 09:39:46 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/24 22:20:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

typedef struct s_redi
{
	int				type;
	char			*put;
	struct	s_redi	*next;
} t_redi;

typedef struct s_pipes
{
	int 			builtin;
	char			put[2];
	char			**command;
	int				error;
	int				exe;
	struct	s_redi	*redi;
	struct	s_pipes	*next;
}	t_pipes;

typedef struct	s_parser
{
	struct s_pipes	*pipe;
	struct s_parser *next;
}				t_parser;

t_parser	*parser(char **vars);
t_parser	*add_parser(t_parser *parser, t_parser *next);
t_parser	*parser_new(char **lexer, int *i);
t_parser	*init_parser(char **lexer, int *i);
t_pipes		*add_pipe(t_pipes *pipe, t_pipes *next);
t_pipes		*init_new(t_pipes *t_new, char **lexer, int *i);
t_pipes		*pipe_new(char **lexer, int *i);
t_pipes		*init_pipes(char **lexer, int *i);
char		**init_command_pipe(char **command, char **lexer, int *i);
int			nbr_command_line(char **lexer);
t_pipes		*init_output(t_pipes *t_new, char **lexer, int deb);
t_redi		*init_put(t_redi *t_new, char **lexer, int *i);
int			nbr_words_exe(char **lexer, int *i);
int			words_command(char **lexer, int i);
char		**malloc_tb_str(char **dst, char **in, int size);
void		free_parser(t_parser *parser);


#endif
