/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:31 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 22:02:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int ft_number(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (ft_isdigit(str[i++]) != 1)
			return (0);
	}
	return (1);
}

void		ft_exit(t_path *path,t_pipes *pipes)
{
	int a;
	if (pipes->command[1] == NULL)
	{
		ft_free(path->parser, path);
		exit(EXIT_SUCCESS);
	}
	if (pipes->command[2] == NULL)
	{
		if (ft_number(pipes->command[1]) == 1)
		{
			a = ft_atoi(pipes->command[1]);
		ft_free(path->parser, path);
		exit(a);
		}
		else
		{
			ft_free(path->parser, path);
		ft_putstr_fd("ERROR\n",2);
		exit(2);
		}
	}
	if (ft_number(pipes->command[1]) == 1)
			ft_putstr_fd("ERROR\n",2);
	else
	{
		ft_free(path->parser, path);
		ft_putstr_fd("ERROR\n",2);
		exit(2);
	}
}