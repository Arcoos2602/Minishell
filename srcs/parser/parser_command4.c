/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:26:09 by thomas            #+#    #+#             */
/*   Updated: 2021/09/29 13:53:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ftsizecommand(char **command, char **lexer)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0' || ft_compare_c_to_s('\"', lexer[i]))
			cpt++;
		i++;
	}
	return (cpt);
}

char	**ft_finish_command(char **command, char **lexer)
{
	int		i;
	int		cpt;
	char	**dest;

	if (command == NULL || lexer == NULL)
		return (NULL);
	dest = malloc(sizeof(char *) * (ftsizecommand(command, lexer) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	cpt = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0' || ft_compare_s_to_s("\"'", lexer[i]))
			dest[cpt++] = ft_strdup(command[i]);
		i++;
	}
	dest[cpt++] = NULL;
	i = 0;
	while (command[i] != NULL)
		free(command[i++]);
	free(command);
	return (dest);
}

static char	**comand_malloc(char **command, char **lexer, t_path *paths)
{
	int	n;
	int	i;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
		{
			command[i++] = parse(lexer[n], paths);
			if (command[i - 1] == NULL)
				i--;
		}
		else
			n++;
	}
	return (ft_finish_command(command, lexer));
}

static int	command_size(char **lexer, t_path *paths)
{
	int		i;
	int		n;
	char	*buf;
	char	*dest;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		buf = ft_strdup(lexer[n]);
		dest = line_env(buf, paths);
		printf("%s ", dest);
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
			i++;
		else
			n++;
	}
	printf("\n");
	return (i);
}

char	**init_command_pipe(char **command, char **lexer, int *i, t_path *paths)
{
	int		size;

	if (lexer[0] != NULL)
	{
		size = command_size(&lexer[*i], paths);
		command = malloc(sizeof(char *) * (size + 1));
		if (command == NULL)
			return (NULL);
		command[size] = NULL;
		command = comand_malloc(command, &lexer[*i], paths);
		if (command == NULL)
			return (NULL);
		return (command);
	}
	return (NULL);
}
