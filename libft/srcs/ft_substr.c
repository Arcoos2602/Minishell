/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:53:48 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/16 12:58:28 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tail(char const *s, unsigned int start, size_t len)
{
	int		i;

	i = 1;
	while (s[start + i] != '\0' && i < (int)len)
		i++;
	if (s[start + i] == '\0' && i >= (int)len)
		i++;
	return (i + 1);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;

	i = -1;
	if (!s)
		return (0);
	while (i++ != (int)start)
		if (s[i] == '\0')
		{
			if (!(dst = ft_calloc(1, 1)))
				return (0);
			return (dst);
		}
	if (!(dst = malloc(tail(s, start, len))))
		return (0);
	i = 0;
	while (s[start + i] != '\0' && i < (int)len)
	{
		dst[i] = s[start + i];
		i++;
	}
	if (s[start + i] == '\0' && i >= (int)len)
		i++;
	dst[i] = '\0';
	return (dst);
}
