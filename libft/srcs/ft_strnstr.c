/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:39:39 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/16 12:39:30 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int	comt;
	int	nb;

	comt = 0;
	nb = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (nb <= (int)len && str[nb] != '\0')
	{
		while (to_find[comt] == str[nb + comt] && to_find[comt] != '\0'
			&& (nb + comt) <= (int)len)
			comt++;
		if (to_find[comt] == '\0' && (nb + comt <= (int)len))
			return ((char*)&str[nb]);
		comt = 0;
		nb++;
	}
	return (0);
}
