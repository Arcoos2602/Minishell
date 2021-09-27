/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:14 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 02:09:17 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	ft_echo2(t_pipes *pipes, int i, int option)
{
	while (pipes->command[i] != NULL)
	{
		ft_putstr_fd(pipes->command[i], 1);
		i++;
		if (pipes->command[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (option == 0)
		ft_putchar_fd('\n', 1);
}

void	ft_echo(t_pipes *pipes)
{
	int		i;
	int		option;
	int		j;
	int		finish;

	i = 1;
	finish = 0;
	option = 0;
	j = 0;
	while (pipes->command[i] != NULL && finish == 0
		&& pipes->command[i][j] == '-')
	{
		j = 0;
		while (pipes->command[i][j] && pipes->command[i][++j] == 'n')
			;
		if (pipes->command[i][j] == '\0')
		{
			option = 1;
			i++;
		}
		else
			finish = 1;
	}
	ft_echo2(pipes, i, option);
}
