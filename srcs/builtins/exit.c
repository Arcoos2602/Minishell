/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:31 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 02:12:06 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	ft_number(char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i++]) != 1)
			return (0);
		num = 1;
	}
	return (num);
}

void	numeric_argument(char *str, t_path *path)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	ft_free(path->parser, path);
	exit(2);
}

int	is_valid(char *str)
{
	int	i;
	int	size;
	int	neg;

	neg = 0;
	i = 0;
	if (str[i] == '-')
	{
		neg++;
		i++;
	}
	while (str[i] == '0')
		i++;
	size = ft_strlen(&str[i]);
	if (size > 19)
		return (-1);
	if (size == 19)
	{
		if (neg == 0 && ft_strncmp(&str[i], "9223372036854775808", 19) >= 0)
			return (-1);
		if (neg == 1 && ft_strncmp(&str[i], "9223372036854775809", 19) >= 0)
			return (-1);
	}
	return (1);
}

void	ft_exit(t_path *path, t_pipes *pipes)
{
	int	a;

	if (pipes->command[1] == NULL)
	{
		ft_free(path->parser, path);
		exit(EXIT_SUCCESS);
	}
	if (pipes->command[2] == NULL)
	{
		if (ft_number(pipes->command[1]) == 1)
		{
			if (is_valid(pipes->command[1]) == -1)
				numeric_argument(pipes->command[1], path);
			a = ft_atoi(pipes->command[1]);
			ft_free(path->parser, path);
			exit(a);
		}
		else
			numeric_argument(pipes->command[1], path);
	}
	if (ft_number(pipes->command[1]) == 1)
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
		path->exit_status = 127;
	}
	else
		numeric_argument(pipes->command[1], path);
}
