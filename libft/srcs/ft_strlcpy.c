/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:43:20 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/26 18:14:36 by user42           ###   ########.fr       */
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
	//		ft_putchar_fd(src[nb],2);
			nb++;
		}
		if (nb < n)
			dest[nb] = '\0';
		while (src[nb] != '\0')
			nb++;
	}
	return (nb);
}
