/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:09:05 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/28 14:04:35 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

char	*ft_special(char *buf)
{
	int		i;
	int		cpt;
	char	*dest;

	cpt = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i++] == '\'')
			cpt++;
	}
	if (cpt == 0)
		return (buf);
	dest = malloc(i + (4 * cpt) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	cpt = 0;
	replace_quotes(dest, buf, &i, &cpt);
	free(buf);
	return (dest);
}

char	*fill(char **buf, char *dest, int *nbr)
{
	if (buf[*nbr][0] != '\0')
	{
		buf[*nbr] = ft_special(buf[*nbr]);
		dest = ft_strjoin(dest, "'");
		dest = ft_strjoin(dest, buf[*nbr]);
		free(buf[*nbr]);
		++*nbr;
		if (buf[*nbr] != NULL)
			dest = ft_strjoin(dest, "' ");
	}
	else
		++*nbr;
	return (dest);
}

static char	**exit_value(char **buf, int *i, t_path *path)
{
	buf = malloc(sizeof(char *) * 2);
	buf[0] = ft_itoa(path->exit_status);
	buf[1] = NULL;
	++*i;
	return (buf);
}

void	init_values_and_free(int *i, int *tmp, int *nbr)
{
	*tmp = *i;
	++*i;
	*nbr = 0;
}

char	*add_env_line(char *str, int *i, t_path *path)
{
	char	**buf;
	char	*dest;
	int		tmp;
	int		nbr;

	init_values_and_free(i, &tmp, &nbr);
	dest = NULL;
	buf = NULL;
	if (str[*i] == '?')
		buf = exit_value(buf, i, path);
	else
		buf = ft_split(ft_dol(str, i, path), ' ');
	if (buf == NULL || buf[0] == NULL)
		return (str);
	dest = ft_strndup(str, tmp);
	while (buf[nbr] != NULL)
		dest = fill(buf, dest, &nbr);
	if (buf[nbr - 1][0] != '\0')
		dest = ft_strjoin(dest, "'");
	buf[0] = ft_strndup(&str[*i], ft_strlen(&str[*i]));
	dest = ft_strjoin(dest, buf[0]);
	free(str);
	free(buf[0]);
	free(buf);
	return (dest);
}
