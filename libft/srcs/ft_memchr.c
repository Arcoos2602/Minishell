/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:54:18 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 01:12:47 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*srcs;

	srcs = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		if (srcs[i] == (unsigned char)c)
			return ((void *)(s));
		s++;
		i++;
	}
	return (NULL);
}
