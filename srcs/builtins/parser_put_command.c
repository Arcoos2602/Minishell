/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_put_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:44:28 by user42            #+#    #+#             */
/*   Updated: 2021/09/29 12:45:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

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
	else if (ft_compare_c_to_s(str[*i], "'\" $") || str[*i] == '\0')
	{
		dest = ft_strjoin(dest, "$");
	}
	else
		dest = ft_strjoin(dest, ft_dol(str, i, path));
	return (dest);
}

char	*parse_put(char *str, t_path *path)
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
