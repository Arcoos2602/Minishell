/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/02/02 13:55:17 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/13 15:01:43 by tcordonn         ###   ########.fr       */
=======
/*   Created: 2021/02/03 10:10:25 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/09 14:38:13 by gbabeau          ###   ########.fr       */
>>>>>>> parser
/*                                                                            */
/* ************************************************************************** */

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

<<<<<<< HEAD
typedef struct	s_bi_parser
{
	char					*command;
	struct	s_bi_parser		*left;
	struct	s_bi_parser		*rigth;
}				t_bi_parser;

int				lexer(t_main *vars);
t_bi_parser		*parser(char *vars);
int				init_all(t_main	*vars);
int				not_handled(char c, char c_next);
char			**token(char *str);
int				check_char(char c);
int				separators(char	c);
int				quote(char *str);
int				get_next_line(int fd, char **line);
=======
int			lexer(t_main *vars);
int			init_all(t_main	*vars);
char		**ft_split_command(char const *str, char *charset);
int			get_next_line(int fd, char **line);
>>>>>>> parser

#endif
