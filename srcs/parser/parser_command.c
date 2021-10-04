/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/10/04 15:19:44 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ft_count(char *str, int *i, char *test)
{
	int	cpt;

	cpt = 0;
	while (str[*i] != '\0' && !ft_compare_c_to_s(str[*i], test))
	{
		cpt++;
		++*i;
	}
	return (cpt);
}

int	ft_count_dol(char *str, int *i, char *test)
{
	int	cpt;

	cpt = 0;
	while (str[*i] != '\0' && ft_compare_c_to_s(str[*i], test))
	{
		cpt++;
		++*i;
	}
	return (cpt);
}

char	*ft_dol(char *str, int *i, t_path *path)
{
	char	*env;
	char	*buff;
	int		cpt;

	cpt = ft_count_dol(str, i, ENV);
	env = ft_substr(str, *i - cpt, cpt);
	buff = ft_getenv(path->path, env);
	free(env);
	return (buff);
}

static int	command_size(char **lexer)
{
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
			i++;
		else
			n++;
	}
	return (i);
}

char	**init_command_pipe(char **command, char **lexer, int *i, t_path *paths)
{
	int	size;

	if (lexer[0] != NULL)
	{
		size = command_size(&lexer[*i]);
		command = malloc(sizeof(char *) * (size + 1));
		if (command == NULL)
			return (NULL);
		command[size] = NULL;
		command = comand_malloc(command, &lexer[*i]);
		command = command_trad(command, paths, size);
		command = split_command(command, &size);
		command = comand_malloc_2(command, paths, size);
		if (command == NULL)
			return (NULL);
		return (command);
	}
	return (NULL);
}
