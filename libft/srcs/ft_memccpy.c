/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:59:56 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/16 12:00:19 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*a;
	unsigned char		*b;
	int					i;

	a = src;
	b = dest;
	i = 0;
	while (n--)
	{
		b[i] = a[i];
		if (b[i] == (unsigned char)c)
		{
			i++;
			return (&dest[i]);
		}
		i++;
	}
	return (NULL);
}
