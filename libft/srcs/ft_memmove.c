/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:52:03 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/14 14:44:57 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*ndst;
	const char	*nsrc;

	ndst = dst;
	nsrc = src;
	if (ndst == nsrc)
		return (dst);
	if (ndst < nsrc)
		while (n--)
			*ndst++ = *nsrc++;
	else
	{
		ndst += n - 1;
		nsrc += n - 1;
		while (n--)
			*ndst-- = *nsrc--;
	}
	return (dst);
}
