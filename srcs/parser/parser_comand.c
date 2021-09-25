/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/25 18:00:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

static int	ft_count(char *str, int *i, char *test)
{
	int cpt;

	cpt = 0;
	while (str[*i] != '\0' && !ft_compare_c_to_s(str[*i], test))
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

	cpt = ft_count(str, i,"'$ \" | > <");
	env = ft_substr(str, *i - cpt, cpt); // env = null
		printf("%s\n", env);
	buff = ft_getenv(path->path, env);
	free(env);
	return (buff);
}

char	*double_quotes(char *str, int *i, t_path *path)
{
	char	*buff;
	char	*env;
	int		cpt;
	char	*dst;


	dst = NULL;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
		{ 
			++*i;
			dst = ft_strjoin(dst, ft_dol(str, i, path));
			free(env);
			//free(buff);
		}
		else
		{
			cpt = ft_count(str, i, "$\"");
			buff = ft_substr(str, *i - cpt, cpt);
			dst = ft_strjoin(dst, buff);
			free(buff); 
		}
		++*i;
	}
	return (dst);
}

char	*parse(char *str, t_path *path)
{
	int		i;
	char	*dest;
	int		cpt;
	char	*buff;

	dest = NULL;
	i = 0;
	cpt = 0;
	while (str[i])
	{
		cpt = ft_count(str, &i, "'$\"");
		printf("cpt : %d i : %d\n", cpt, i);
		if (cpt != 0)
		{
			buff = ft_substr(str, i - cpt, cpt);
			printf("%s\n", buff);
			dest = ft_strjoin(dest, buff);
			printf("%s\n", dest);
			free(buff);
		}
		if (str[i] == '"')
		{
			++i;
			buff = double_quotes(str, &i, path);
			dest = ft_strjoin(dest, buff);
			free(buff);
		}
		else if(str[i] == '\'')
		{
			++i;
			cpt = ft_count(str, &i, "'");
			buff = ft_substr(str, i - cpt, cpt);
			dest = ft_strjoin(dest, buff);
			free(buff);
		}
		else if (str[i] == '$')
		{
			++i;
			dest = ft_strjoin(dest, ft_dol(str, &i, path));
		//	free(buff);
		}
		printf("AAAAAa\n");
	}
	printf("%s\n", dest);
	return (dest);
}

static char	**comand_malloc(char **command, char **lexer, t_path *paths)
{
	int	n;
	int	i;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|;"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
		{
			command[i++] = parse(lexer[n], paths);
		}
		else
			n++;
	}
	return (command);
}

static int	command_size(char **lexer)
{
	int	i;
	int	n;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|;"))
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
		command = comand_malloc(command, &lexer[*i], paths);
		if (command == NULL)
			return (NULL);
		return (command);
	}
	return (NULL);
}

int	nbr_command_line(char **lexer)
{
	int	i;
	int	nbr_command_line;

	nbr_command_line = 1;
	i = 0;
	while (lexer[i] != NULL)
	{
		if (lexer[i++][0] == ';')
		{
			if (lexer[i] != NULL && ft_compare_c_to_s(lexer[i][0], ";|"))
				return (0);
			nbr_command_line++;
		}
	}
	return (nbr_command_line);
}
