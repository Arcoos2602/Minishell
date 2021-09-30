/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:26:09 by thomas            #+#    #+#             */
/*   Updated: 2021/09/30 05:19:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char	**comand_malloc(char **command, char **lexer)
{
	int	n;
	int	i;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
		{
			command[i++] = ft_strdup(lexer[n]);
			if (command[i - 1] == NULL)
				i--;
		}
		else
			n++;
	}
	return (command);
}

char	**comand_malloc_2(char **command, t_path *paths, int size)
{
	int		n;
	int		i;
	char	**dest;

	dest = malloc(sizeof(char *) * (size + 1));
	dest[size] = NULL;
	n = 0;
	i = 0;
	while (size != i)
	{
		if (command[i] != NULL)
		{
			dest[n] = parse(command[i], paths);
			if (dest[n] != NULL)
				n++;
		}
		i++;
	}
	dest[n] = NULL;
	size = 0;
	while (command[size] != NULL)
		free(command[size++]);
	free(command);
	return (dest);
}

char	**command_trad(char **command, t_path *paths, int size)
{
	int		i;
	char	**dest;

	i = 0;
	dest = malloc(sizeof(char *) * (size + 1));
	if (command == NULL)
		return (NULL);
	while (command[i] != NULL)
	{
		dest[i] = command_trad_2(command[i], paths);
		i++;
	}
	dest[i] = NULL;
	i = 0;
	while (command[i] != NULL)
		free(command[i++]);
	free(command);
	return (dest);
}

char	**split_command(char **command, int *size)
{
	int		i;
	char	**dest;
	int		count;
	int		d;

	i = 0;
	d = 0;
	count = count_tab(command);
	*size = count;
	dest = malloc(sizeof(char *) * (count + 1));
	if (command == NULL)
		return (NULL);
	dest[count] = NULL;
	while (command[i] != NULL)
		dest = command_split_2(dest, command, &i, &d);
	dest[count] = NULL;
	i = 0;
	while (command[i] != NULL)
		free(command[i++]);
	free(command);
	return (dest);
}
