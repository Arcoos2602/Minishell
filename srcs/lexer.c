/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:13:44 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/02 11:31:04 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	count_commands(t_main *vars)
{
		
}

void	print_tab(char **tab)
{
	int		x = 0;
	int		y = 0;

	while (tab[x] != NULL)
	{
		y = 0;
		ft_putchar_fd('[', 1);
		while (tab[x][y] != '\0')
		{
			ft_putchar_fd(tab[x][y], 1);
			y++;
		}
		ft_putchar_fd(']', 1);
		x++;
	}
}

int		lexer(t_main *vars)
{
	int		i;

	i = 0;
	get_next_line(1, &vars->line);
	if (vars->line[0] == '\0')
		vars->lexer = NULL;
	else
	{
		count_commands(vars);
		vars->lexer = ft_split_comm`and(vars->line, ' ');
		print_tab(vars->lexer);
	}
	ft_putstr_fd("\n $", 1);
	return (1);
}
