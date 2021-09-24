/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:13:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 20:18:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	elem(char *str, int *cpt, int *i)
{
	while (str[*i] != '\0' && !ft_iswhitespace(str[*i]) && !token(str[*i]))
	{
		if (count_quote(str, i) == -1)
			return (-1);
		++*i;
	}
	++*cpt;
	return (1);
}

int	cpt(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (str[i] != '\0' && ft_iswhitespace(str[i]))
			i++;
		if (str[i] == '\0')
			return (cpt);
		if (str[i] != '\0' && !ft_iswhitespace(str[i]) && !token(str[i]))
		{
			if (elem(str, &cpt, &i) == -1)
				return (-1);
		}
		if (token(str[i]))
		{
			if (check_error(str, &i, &cpt) == -1)
				return (-1);
		}
	}
	return (cpt);
}

void	fill_quotes(char **tab, char *str, int *i, int *j) // pour "" handle $
{
	int	len;
	int	start;

	len = 0;
	while (str[*i] != '\0' && !ft_iswhitespace(str[*i]) && !token(str[*i]))
	{
		start = *i;
		if (str[*i] == '"')
		{
			while (str[++*i] != '"')
				len++;
			printf("%d\n", len);
			tab[*j] = ft_substr(str, start, len + 2);
			printf("%s\n", tab[*j]);
			++*j;
		}
		++*i;
	}
}

void	fill_token(char **tab, char *str, int *i, int *j)
{
	if (token(str[*i + 1]))
	{
		tab[*j] = ft_strndup(&str[*i], 2);
		*i += 2;
		++*j;
	}
	else
	{
		tab[*j] = ft_strndup(&str[*i], 2);
		++*j;
		++*i;
	}
}

/*void	handle_dollar(char **tab, char *str, int *i)
{
	int	len;
	char	*env_var;

	while (str[*i] != '\0' && !token(str[*i]) && !ft_iswhitespace(str[*i]) && str[*i] != '$')
	{
		++*i;
		len++;
	}
	ft_getenv();
}*/

void	fill_tab(char **tab, char *str, char **paths)
{
	int	i;
	int	j;
	int	start;
	int	len;

	(void)paths;
	start = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		len = 0;
		while (str[i] != '\0' && ft_iswhitespace(str[i]))
			i++;
		//fill_quotes(tab, str, &i, &j);
		start = i;
		while (str[i] != '\0' && !token(str[i]) && !ft_iswhitespace(str[i++]))
			len++;
		/*if (str[i] == '$')
			handle_dollar(tab, str, &i);*/
		tab[j] = ft_substr(str, start, len);
		j++;
		if (token(str[i]))
			fill_token(tab, str, &i, &j);
	}
	tab[j] = NULL;
	j = 0;
	while (tab[j] != NULL)
	{
		printf("%s\n", tab[j++]);
	}
}

void	fill_var(char **tab, char *str,  int len[2], char **paths)
{
	len[1]++;
	printf("%s\n", &str[len[1]]);
	tab[len[0]] = ft_strdup(ft_getenv(paths, &str[len[1]]));
	printf("%s\n", tab[len[0]]);
}

void	print_tab(char **tab)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (tab[x] != NULL)
	{
		y = 0;
		ft_putchar_fd('[', 1);
		while (tab[x][y] != '\0')
		{
			ft_putchar_fd(tab[x][y], 1);
			y++;
		}
		ft_putchar_fd(']', 1);
		x++;
	}
}

char	**tokenization(char *str, char **paths)
{
	char	**tab;
	int		cpt_l;

	(void)paths;
	tab = NULL;
	if (str == NULL)
		return (NULL);
	cpt_l = cpt(str);
	if (cpt_l < 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (cpt_l + 1));
	if (tab == NULL)
		return (NULL);
	printf("cpt : %d\n", cpt_l);
	fill_tab(tab, str, paths);
	//print_tab(tab);
	//exit (EXIT_SUCCESS);
	return (tab);
}
