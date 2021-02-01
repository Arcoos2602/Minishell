/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:23:58 by tcordonn          #+#    #+#             */
/*   Updated: 2021/01/29 14:17:28 by tcordonn         ###   ########.fr       */
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

typedef struct	s_command
{
	char	*line;
	char	**commands_tab;
	int		command_nbr;
}				t_command;


int		parser(t_command *vars);
int		init_all(t_command	*vars);
int		get_next_line(int fd, char **line);

#endif