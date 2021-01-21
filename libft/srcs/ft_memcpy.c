/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:27:44 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/16 12:12:42 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*a;
	const char	*b;

	a = dest;
	b = src;
	if (!src && !dest)
		return (0);
	while (n--)
		*a++ = *b++;
	return (dest);
}
