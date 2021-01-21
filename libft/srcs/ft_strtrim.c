/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:11:16 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/18 11:32:02 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		debut(char const *s1, char const *set)
{
	int		i;
	int		deb;

	i = 0;
	deb = 0;
	while (set[i] && s1[deb] != '\0')
	{
		i = 0;
		while (set[i] != s1[deb] && set[i] != '\0')
			i++;
		if (set[i] == s1[deb])
			deb++;
	}
	return (deb);
}

static int		fin(char const *s1, char const *set)
{
	int		tail;
	int		i;

	tail = 0;
	while (s1[tail] != '\0')
		tail++;
	tail--;
	i = 0;
	while (set[i] && tail >= 0)
	{
		i = 0;
		while (set[i] != s1[tail] && set[i] != '\0')
			i++;
		if (set[i] == s1[tail])
			tail--;
	}
	return (tail);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		d;
	int		f;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	f = fin(s1, set);
	d = debut(s1, set);
	if (f - d < 0)
	{
		if (!(s = ft_calloc(1, 1)))
			return (0);
		return (s);
	}
	if (!(s = malloc(f - d + 2)))
		return (0);
	while (f - d >= i)
	{
		s[i] = s1[i + d];
		i++;
	}
	s[i] = '\0';
	return (s);
}
