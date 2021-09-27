/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:13:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 11:08:42 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	fill_token(char **tab, char *str, int *i, int *j)
{
	if (str[*i] == str[*i + 1])
	{
		tab[*j] = ft_strndup(&str[*i], 2);
		*i += 2;
		++*j;
	}
	else
	{
		tab[*j] = ft_strndup(&str[*i], 1);
		++*j;
		++*i;
	}
}

void	quotes(char *str, int *i, int *len)
{
	if (str[*i] == '"')
	{
		while (str[*i] != '\0' && str[++*i] != '"')
			++*len;
		++*len;
	}
	else if (str[*i] == '\'')
	{
		while (str[*i] != '\0' && str[++*i] != '\'')
			++*len;
		++*len;
	}
}

void	init_vars(int *start, int *len, int *i, int *j)
{
	*start = 0;
	*i = 0;
	*j = 0;
	*len = 0;
}

void	fill_tab(char **tab, char *s, int cpt_l)
{
	int	i;
	int	j;
	int	start;
	int	l;

	init_vars(&start, &l, &i, &j);
	while (s[i] != '\0' && j < cpt_l)
	{
		l = 0;
		while (s[i] != '\0' && ft_iswhitespace(s[i]))
			i++;
		start = i;
		while (s[i] != '\0' && !token(s[i]) && !ft_iswhitespace(s[i]))
		{
			quotes(s, &i, &l);
			l++;
			i++;
		}
		if (l != 0 && (s[i] == '\0' || token(s[i]) || ft_iswhitespace(s[i])))
			tab[j++] = ft_substr(s, start, l);
		while (s[i] != '\0' && ft_iswhitespace(s[i]))
			i++;
		if (token(s[i]))
			fill_token(tab, s, &i, &j);
	}
}

char	**tokenization(char *str, t_path *paths)
{
	char	**tab;
	int		cpt_l;

	tab = NULL;
	if (str == NULL)
		return (NULL);
	cpt_l = cpt(str);
	if (cpt_l < 0)
	{
		paths->exit_status = 2;
		return (NULL);
	}
	tab = malloc(sizeof(char *) * (cpt_l + 1));
	if (tab == NULL)
		return (NULL);
	tab[cpt_l] = NULL;
	fill_tab(tab, str, cpt_l);
	return (tab);
}
