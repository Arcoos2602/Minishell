/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:10:25 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/03 10:19:14 by gbabeau          ###   ########.fr       */
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
# define BUFFER_SIZE 1096

typedef struct	s_main
{
	char	*line;
	char	**lexer;
	int		command_nbr;
}				t_main;

typedef struct	s_parser
{
	char		***command;
	char		**put[3];
}				t_parser;

int			lexer(t_main *vars);
t_parser	*parser(char **vars);
int			init_all(t_main	*vars);
char		**ft_split_command(char const *str, char *charset);
int			get_next_line(int fd, char **line);

#endif
