/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:42 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/26 15:26:40 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H

typedef struct s_pipes
{
	char			**command;
	char			***input;
	char			***output_s;
	char			***output_d;
	struct s_pipes	*next;
}	t_pipes;

typedef struct	s_parser
{
	struct		s_pipes	*pipe;
	struct		s_parser *next;
}				t_parser;

t_parser	*parser(char **vars);
t_parser	*add_parser(t_parser *parser, t_parser *next);
t_parser	*parser_new(char **lexer, int *i);
t_parser	*init_parser(char **lexer, int *i);
t_pipes		*init_put(t_pipes *t_new, char **lexer, int *i);
t_pipes		*add_pipe(t_pipes *pipe, t_pipes *next);
t_pipes		*init_new(t_pipes *t_new, char **lexer, int *i);
t_pipes		*pipe_new(char **lexer, int *i);
t_pipes		*init_pipes(char **lexer, int *i);
char		**init_command_pipe(char **command, char **lexer, int *i);
int			nbr_command_line(char **lexer);
char		**init_input_2(char **input, char **lexer, int nbr_input, int *i);
char		***init_input(char ***input, char **lexer, int debb);
char		**init_output_3(char **output_1, char **output_2, char **lexer);
void		*init_output_2(t_pipes *pipe,
			char **lexer, int *deb, int nbr);
t_pipes		*init_output(t_pipes *t_new, char **lexer, int deb);
t_pipes		*init_put(t_pipes *t_new, char **lexer, int *i);
int			nbr_words_exe(char **lexer, int *i);
void		*p_malloc(char ***tab, int sizei);
int			words_command(char **lexer, int i);
char		**malloc_tb_str(char **dst, char **in, int size);
int			init_inouput(char **lexer, char *inout);

# endif
