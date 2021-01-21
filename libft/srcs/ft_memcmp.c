/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:31:58 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/16 12:02:02 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*char1;
	const char	*char2;
	int			i;

	char1 = s1;
	char2 = s2;
	i = 0;
	while (n--)
	{
		if ((unsigned char)char1[i] - (unsigned char)char2[i])
			return ((unsigned char)char1[i] - (unsigned char)char2[i]);
		i++;
	}
	return (0);
}
