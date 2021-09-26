/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:43:20 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 01:29:51 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	nb;

	nb = 0;
	if (src)
	{
		while (nb + 1 < n && src[nb] != '\0')
		{
			dest[nb] = src[nb];
			nb++;
		}
		if (nb < n)
			dest[nb] = '\0';
		while (src[nb] != '\0')
			nb++;
	}
	return (nb);
}
