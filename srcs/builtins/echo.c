/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:14 by tcordonn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/15 15:43:00 by tcordonn         ###   ########.fr       */
=======
/*   Updated: 2021/03/15 13:00:48 by tcordonn         ###   ########.fr       */
>>>>>>> parser
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int			var(char *str, char **path)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (str[0] == '$')
	{
		while (path[++i] != NULL)
		{
			j = 0;
			while (path[i][++j] != '=')
				;
			if (ft_strncmp(&str[1], path[i], j) == 0)
			{
				ft_putstr_fd(&path[i][j + 1], 1);
			}
		}
		return (1);
	}
	return (0);
}

void		ft_echo(t_pipes *pipes, char **path)
{
	int		i;

	i = 1;
	if (ft_strncmp(pipes->command[1], "-n", ft_strlen(pipes->command[1])) == 0)
	{
		i++;
		while (pipes->command[i] != NULL)
		{
<<<<<<< HEAD
			ft_putstr_fd(pipes->command[i], 1);
=======
			if (var(pipes->command[i], path) == 0)
				ft_putstr_fd(pipes->command[i], 1);
>>>>>>> parser
			i++;
			if (pipes->command[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while (pipes->command[i] != NULL)
		{
<<<<<<< HEAD
			ft_putstr_fd(pipes->command[i], 1);
=======
			if (var(pipes->command[i], path) == 0)
				ft_putstr_fd(pipes->command[i], 1);
>>>>>>> parser
			i++;
			if (pipes->command[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	exit(EXIT_SUCCESS);
}
