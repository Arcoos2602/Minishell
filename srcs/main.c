/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/01/22 13:12:11 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int		main(int	argc, char **argv)
{
	t_command	vars;
	char		*line;
	(void)argc;
	(void)argv;

	ft_putstr_fd("$ ", 1);
	if ((!init_all(&vars)))
		return (-1);
	while (1)
	{
		parser(&vars);
		free(vars.line);
	}
	return (1);
}
