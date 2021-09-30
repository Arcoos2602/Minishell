/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:14:21 by user42            #+#    #+#             */
/*   Updated: 2021/09/30 06:13:19 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

static int	count_trad_2(char *command)
{
	int	i;

	i = 0;
	while (!ft_compare_c_to_s(command[i], "$'\"") && command[i] != '\0')
		i++;
	return (i);
}

static char	*command_trad_2_1(char *dest, char *command, int *size, int *i)
{
	char	*buf;

	++*size;
	buf = ft_strndup(&command[*i], *size);
	dest = ft_strjoin(dest, buf);
	free(buf);
	*i += *size;
	*size = 0;
	while (!ft_compare_c_to_s(command[*i + *size], "'")
		&& command[*i + *size] != '\0')
		++*size;
	if (command[*i + *size] != '\0')
		++*size;
	++*size;
	buf = ft_strndup(&command[*i], *size);
	dest = ft_strjoin(dest, buf);
	free(buf);
	return (dest);
}

static char	*command_trad_2_2(char *dest, char *command, int *size, int *i)
{
	char	*buf;

	++*size;
	buf = ft_strndup(&command[*i], *size);
	dest = ft_strjoin(dest, buf);
	free(buf);
	*i += *size;
	*size = 0;
	while (!ft_compare_c_to_s(command[*i + *size], "\"")
		&& command[*i + *size] != '\0')
		++*size;
	if (command[*i + *size] != '\0')
		++*size;
	++*size;
	buf = ft_strndup(&command[*i], *size);
	dest = ft_strjoin(dest, buf);
	free(buf);
	return (dest);
}

static char	*command_trad_2_3(char *dest, char *command, int *size, int *i)
{
	char	*buf;

	buf = ft_strndup(&command[*i], *size);
	dest = ft_strjoin(dest, buf);
	*i += *size;
	*size = 0;
	free(buf);
	return (dest);
}

char	*command_trad_2(char *command, t_path *paths)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	dest = NULL;
	while (command[i] != '\0')
	{
		size = count_trad_2(&command[i]);
		if (command[i + size] == '\'')
			dest = command_trad_2_1(dest, command, &size, &i);
		else if (command[i + size] == '"')
			dest = command_trad_2_2(dest, command, &size, &i);
		else if (command[i + size] == '$')
		{
			dest = command_trad_2_3(dest, command, &size, &i);
			dest = parse_4(&i, command, dest, paths);
			if (command[i] == '?' && command[i - 1] == '$')
				i++;
		}
		else if (command[i + size] == '\0')
			dest = ft_strjoin(dest, &command[i]);
		i += size;
	}
	return (dest);
}
