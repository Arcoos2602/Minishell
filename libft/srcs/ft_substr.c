/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:53:48 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 01:38:49 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *s, unsigned int start, size_t len)
{
	int		i;

	i = 1;
	while (s[start + i] != '\0' && i < (int)len)
		i++;
	if (s[start + i] == '\0' && i >= (int)len)
		i++;
	return (i + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	while (i++ != (int)start)
	{
		if (s[i] == '\0')
			return (ft_calloc(1, 1));
	}
	result = malloc(sizeof(char) * ft_size(s, start, len));
	if (!result)
		return (NULL);
	i = 0;
	while (i < (int)len && s[start + i] != '\0')
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
