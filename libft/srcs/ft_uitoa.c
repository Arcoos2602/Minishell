/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:19:17 by gbabeau           #+#    #+#             */
/*   Updated: 2020/01/30 12:54:39 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_compt(unsigned int nb, unsigned int i)
{
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	if (nb / 10)
		return (ft_compt(nb / 10, i + 1));
	return (i + 1);
}

static int		ft_chifre(unsigned int n, unsigned int a, unsigned int i)
{
	int	dix;

	dix = 1;
	while (a < i)
	{
		a++;
		dix *= 10;
	}
	n /= dix;
	return ((n % 10));
}

char			*ft_uitoa(unsigned int n)
{
	char				*dest;
	unsigned int		i;
	unsigned int		a;

	a = 0;
	n += 48;
	n -= 48;
	i = ft_compt(n, 0);
	if (!(dest = malloc(i + 1)))
		return (0);
	while (a != i)
	{
		dest[a] = (char)(ft_chifre(n, a + 1, i) + 48);
		a++;
	}
	dest[a] = 0;
	return (dest);
}
