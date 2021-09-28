/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:24:32 by thomas            #+#    #+#             */
/*   Updated: 2021/09/28 16:14:04 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char	*quote_exit(int *i, t_path *path)
{
	char	*buf;
	char	*dest;

	dest = NULL;
	buf = ft_itoa(path->exit_status);
	dest = ft_strjoin(dest, buf);
	++*i;
	free(buf);
	return (dest);
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
			dst = quote_exit(i, path);
		else if (buff != NULL)
			dst = ft_strjoin(dst, buff);
		else if (str[*i] != '\0' && str[*i - 1] == '$')
			dst = ft_strjoin(dst, "$");
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
