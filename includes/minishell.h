/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:55:17 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/16 14:45:55 by tcordonn         ###   ########.fr       */
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
t_bi_parser		*parser(char *vars);
int				init_all(t_main	*vars);
int				not_handled(char c, char c_next);
char			**token(char *str);
void			cpt2(char *str, int *i, int *cpt);
int				check_multi(char *str);
int				check_char(char c);
int				separators(char	c);
int				quote(char *str);
int				get_next_line(int fd, char **line);

#endif
