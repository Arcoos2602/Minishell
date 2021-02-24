/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:42 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/22 12:54:59 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H

typedef struct s_pipe
{
	char			**command;
	char			***input;
	char			***output_s;
	char			***output_d;
	struct s_pipe	*next;
}	t_pipe;

typedef struct	s_parser
{
	struct		s_pipe	*pipe;
	struct		s_parser *next;
}				t_parser;

t_parser	*parser(char **vars);
t_parser	*add_parser(t_parser *parser, t_parser *next);
t_parser	*parser_new(char **lexer, int *i);
t_parser	*init_parser(char **lexer, int *i);
t_pipe		*init_put(t_pipe *t_new, char **lexer, int *i);
t_pipe		*add_pipe(t_pipe *pipe, t_pipe *next);
t_pipe		*init_new(t_pipe *t_new, char **lexer, int *i);
t_pipe		*pipe_new(char **lexer, int *i);
t_pipe		*init_pipe(char **lexer, int *i);
char		**init_command_pipe(char **command, char **lexer, int *i);
int			nbr_command_line(char **lexer);
char		**init_input_2(char **input, char **lexer, int nbr_input, int *i);
char		***init_input(char ***input, char **lexer, int debb);
char		**init_output_3(char **output_1, char **output_2, char **lexer);
void		*init_output_2(t_pipe *pipe,
		char **lexer, int *deb, int nbr);
t_pipe		*init_output(t_pipe *t_new, char **lexer, int deb);
t_pipe		*init_put(t_pipe *t_new, char **lexer, int *i);
int			nbr_words_exe(char **lexer, int *i);
void		*p_malloc(char ***tab, int sizei);
int			words_command(char **lexer, int i);
char		**malloc_tb_str(char **dst, char **in, int size);
int			init_inouput(char **lexer, char *inout);

# endif
