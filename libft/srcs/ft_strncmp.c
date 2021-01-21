/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:45:07 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/15 12:06:49 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	nb;

	nb = 0;
	if (n == 0)
		return (0);
	while (s1[nb] == s2[nb] && n > (nb + 1) &&
		(s1[nb] != '\0' || s2[nb] != '\0'))
		nb++;
	return ((unsigned char)s1[nb] - s2[nb]);
}
