/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:31 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 15:44:06 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

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

void	specified_exit(t_pipes *pipes, t_path *path, int *a)
{
	if (ft_number(pipes->command[1]) == 1)
	{
		if (is_valid(pipes->command[1]) == -1)
			numeric_argument(pipes->command[1], path);
		*a = ft_atoi(pipes->command[1]);
		ft_free(path->parser, path);
		exit(*a);
	}
	else
		numeric_argument(pipes->command[1], path);
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
		specified_exit(pipes, path, &a);
	if (ft_number(pipes->command[1]) == 1)
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
		path->exit_status = 127;
	}
	else
		numeric_argument(pipes->command[1], path);
}
