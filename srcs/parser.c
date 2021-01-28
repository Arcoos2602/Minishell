/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:11:46 by tcordonn          #+#    #+#             */
/*   Updated: 2021/01/26 15:37:16 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	count_command(char *line, int command_nbr)
{
	int		i;

	i = 0;

}

int		parse_command(char *line, char **commands_table, int command_nbr)
{
	int		i;

	i = 0;
	count_command(line, command_nbr);
	if (command_nbr == 0)
	{
		printf("bash: %s: command not found\n", line);
		return (1);
	}
	return (1);
}

int		parser(t_command *vars)
{
	get_next_line(1, &vars->line);
	if (vars->line[0] != '\0')
	{
		parse_command(vars->line, vars->commands_tab, // no check just parsing
				vars->command_nbr);
		//parse_special_characters();
	}
	ft_putstr_fd("$ ", 1);
	//exec();
	return (1);
}
