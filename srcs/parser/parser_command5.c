/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:14:07 by user42            #+#    #+#             */
/*   Updated: 2021/09/30 05:37:54 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	count_tab2(char *command)
{
	int	i;
	int	cpt;

	i = -1;
	cpt = 1;
	while (command[++i] != '\0')
	{
		if (command[i] == '\'')
			while (command[i] != '\0' && command[++i] != '\'')
				;
		if (command[i] == '"')
			while (command[i] != '\0' && command[++i] != '"')
				;
		if (ft_iswhitespace(command[i]) && command[++i] != '\0')
		{
			while (ft_iswhitespace(command[i]))
				i++;
			if (command[i] != '\0')
				cpt++;
		}
	}
	return (cpt);
}

int	count_tab(char **command)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (command[i] != NULL)
	{
		cpt += count_tab2(command[i]);
		i++;
	}
	return (cpt);
}

static void	loop_split_2(char *command, int *x)
{
	if (command[*x] == '\'')
		while (command[*x] != '\0' && command[++*x] != '\'')
			;
	if (command[*x] == '"')
		while (command[*x] != '\0' && command[++*x] != '"')
			;
}

static void	init_split_2(int *x, int *dep, int *cpt)
{
	*x = -1;
	*dep = 0;
	*cpt = 1;
}

char	**command_split_2(char **dest, char **command, int *i, int *d)
{
	int	x;
	int	cpt;
	int	dep;

	init_split_2(&x, &dep, &cpt);
	while (command[*i] != NULL && command[*i][++x] != '\0')
	{
		loop_split_2(command[*i], &x);
		if (ft_iswhitespace(command[*i][x]) && command[*i][++x] != '\0')
		{
			dest[*d] = ft_strndup(&command[*i][dep], x - dep - 1);
			++*d;
			while (command[*i] != NULL && ft_iswhitespace(command[*i][x]))
				x++;
			dep = x;
			if (command[*i] != NULL && command[*i][x] != '\0')
				cpt++;
		}
	}
	if (command[*i] != NULL)
		dest[*d] = ft_strdup(&command[*i][dep]);
	++*i;
	++*d;
	return (dest);
}
