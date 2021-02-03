/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:55:17 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/03 14:31:07 by tcordonn         ###   ########.fr       */
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
//char			**ft_split_command(char const *str, char *charset);
int				get_next_line(int fd, char **line);

#endif
