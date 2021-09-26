/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:35:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 01:23:25 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cpt(char const *str, char charset)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		while (str[i] == charset && str[i] != '\0')
			i++;
		if (str[i] != charset && str[i] != '\0')
		{
			a++;
			while (str[i] != charset && str[i] != '\0')
				i++;
		}
	}
	i--;
	return (a);
}

static int	initalisation(char **end, char const *str, char charset)
{
	int	b;
	int	a;
	int	i;

	i = 0;
	a = 0;
	b = 0;
	while (b < cpt(str, charset))
	{
		a = 0;
		while (str[i] == charset && str[i] != '\0')
			i++;
		while (str[i] != '\0' && str[i++] != charset)
			a++;
		end[b] = (char *)malloc(sizeof(char) * (a + 1));
		if (end[b] == NULL)
			return (0);
		b++;
	}
	end[b] = 0;
	return (1);
}

static void	init_var(int *a, int *b, int *i, char **end)
{
	*a = 0;
	*i = 0;
	*b = 0;
	end = 0;
}

char	**ft_split(char const *str, char charset)
{
	char	**end;
	int		i;
	int		a;
	int		b;

	init_var(a, b, i, end);
	if (!str)
		return (0);
	end = malloc(sizeof(char *) * (cpt(str, charset) + 1));
	if (!end || !initalisation(end, str, charset))
		return (0);
	while (str[i] == charset && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		b = 0;
		while (str[i] != charset && str[i] != '\0')
			end[a][b++] = str[i++];
		while (str[i] == charset && str[i] != '\0')
			i++;
		end[a++][b] = '\0';
	}
	return (end);
}
