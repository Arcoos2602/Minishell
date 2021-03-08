/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/03/08 15:47:05 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"


static char ** comand_malloc(char **command, char **lexer)
{
	int n;
	int i;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0],"|;"))
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
			command[i++] = ft_strdup(lexer[n]);
		else
			n++;
	command[i]= NULL;
		return (command);
}

static int	command_size(char **lexer)
{
	int i;
	int n;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s( lexer[++n][0],"|;"))
	{
		if (0 != (ft_compare_c_to_s(lexer[n][0], "><")))
			n++;
		else
			i++;
	}
return (i);
}

char		**init_command_pipe(char **command, char **lexer, int *i)
{
	int	size;

	if (lexer[0] != NULL)
	{
		size = command_size(lexer);
		if (0 == (command = malloc(sizeof(char *) * command_size(lexer) + 1)))
			return (NULL);
		if (NULL == (command = comand_malloc(command, &lexer[*i])))
			return (NULL);
		return (command);
	}
	return (NULL);
}

int			nbr_command_line(char **lexer)
{
	int		i;
	int		nbr_command_line;

	nbr_command_line = 1;
	i = 0;
	while (lexer[i] != NULL)
		if (lexer[i++][0] == ';')
		{
			if (lexer[i] != NULL && ft_compare_c_to_s(lexer[i][0], ";|"))
				return (0);
			nbr_command_line++;
		}
	return (nbr_command_line);
}
