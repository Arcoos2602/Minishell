/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 13:43:07 by gbabeau          ###   ########.fr       */
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

char	*ft_dol(char *str, int *i, t_path *path)
{
	char	*env;
	char	*buff;
	int		cpt;

	cpt = ft_count(str, i, "'$ \" | > <?");
	env = ft_substr(str, *i - cpt, cpt);
	buff = ft_getenv(path->path, env);
	free(env);
	return (buff);
}

char	*double_quote_2(int *i, char *str, char *dst, t_path *path)
{
	char	*buff;
	int		cpt;

	if (str[*i] == '$')
	{
		++*i;
		buff = ft_dol(str, i, path);
		if (buff == NULL && str[*i] == '?' && str[*i - 1] == '$')
		{
			buff = ft_itoa(path->exit_status);
			dst = ft_strjoin(dst, buff);
			++*i;
			free(buff);
		}
		else if (buff != NULL)
			dst = ft_strjoin(dst, buff);
		else if (str[*i] != '\0' && str[*i - 1] == '$')
		{
			buff = ft_strdup("$");
			dst = ft_strjoin(dst, buff);
			free(buff);
		}
	}
	else
	{
		cpt = ft_count(str, i, "$\"");
		buff = ft_substr(str, *i - cpt, cpt);
		dst = ft_strjoin(dst, buff);
		free(buff);
	}
	return (dst);
}

char	*double_quotes(char *str, int *i, t_path *path)
{
	char	*dst;

	dst = NULL;
	while (str[*i] != '\0' && str[*i] != '"')
		dst = double_quote_2(i, str, dst, path);
	if (dst == NULL)
	{
		dst = malloc(1);
		if (dst == NULL)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	return (dst);
}

char	*parse_1(int *i, char *str, char *dest, int cpt)
{
	char	*buff;

	buff = ft_substr(str, *i - cpt, cpt);
	dest = ft_strjoin(dest, buff);
	free(buff);
	return (dest);
}

char	*parse_3(int *i, char *str, char *dest)
{
	char	*buff;
	int		cpt;

	++*i;
	cpt = ft_count(str, i, "'");
	buff = ft_substr(str, *i - cpt, cpt);
	dest = ft_strjoin(dest, buff);
	++*i;
	free(buff);
	return (dest);
}

char	*parse_2(int *i, char *str, char *dest, t_path *path)
{
	char	*buff;

	++*i;
	buff = double_quotes(str, i, path);
	dest = ft_strjoin(dest, buff);
	++*i;
	free(buff);
	return (dest);
}

char	*parse_4(int *i, char *str, char *dest, t_path *path)
{
	char	*buff;

	++*i;
	if (str[*i] == '?')
	{
		buff = ft_itoa(path->exit_status);
		dest = ft_strjoin(dest, buff);
		free(buff);
	}
	else  if (ft_compare_c_to_s(str[*i], "'\" $") || str[*i] == '\0')
	{
		dest = ft_strjoin(dest, "$");
	}
	else
		dest = ft_strjoin(dest, ft_dol(str, i, path));
	return (dest);
}

char	*parse(char *str, t_path *path)
{
	int		i;
	char	*dest;
	int		cpt;

	dest = NULL;
	i = 0;
	cpt = 0;
	while (str[i])
	{
		cpt = ft_count(str, &i, "'$\"");
		if (cpt != 0)
		{
			dest = parse_1(&i, str, dest, cpt);
		}
		if (str[i] == '"')
			dest = parse_2(&i, str, dest, path);
		else if (str[i] == '\'')
			dest = parse_3(&i, str, dest);
		else if (str[i] == '$')
			dest = parse_4(&i, str, dest, path);
	}
	return (dest);
}

char **ft_finish_command(char **command, char **lexer)
{
	int i;
	int cpt;
	char **dest;

	i = 0;
	if (command == NULL)
		return (NULL);
	cpt = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0' || ft_compare_c_to_s('\"', lexer[i]))
			cpt++;
		i++;
	}
	dest = malloc(sizeof(char *) * (cpt + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	cpt = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0'  || ft_compare_c_to_s('\"',lexer[i]))
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

static int	command_size(char **lexer)
{
	int	i;
	int	n;

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
			if (lexer[i] != NULL && ft_compare_c_to_s(lexer[i][0], "|"))
				return (0);
			nbr_command_line++;
		}
	}
	return (nbr_command_line);
}
