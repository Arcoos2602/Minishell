/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:14 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/18 14:02:14 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void		ft_echo(t_pipes *pipes)
{
	int		i;

	i = 1;
	if (ft_strncmp(pipes->command[1], "-n", ft_strlen(pipes->command[1])) == 0)
	{
		i++;
		while (pipes->command[i] != NULL)
		{
			ft_putstr_fd(pipes->command[i], 1);
			i++;
			if (pipes->command[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while (pipes->command[i] != NULL)
		{
			ft_putstr_fd(pipes->command[i], 1);
			i++;
			if (pipes->command[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	exit(EXIT_SUCCESS);
}
