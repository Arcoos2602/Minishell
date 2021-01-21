/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:57:51 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/18 11:14:02 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_compt(long nb, int i)
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

static int		ft_chifre(long n, int a, int i)
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

char			*ft_itoa(int n)
{
	char	*dest;
	int		i;
	int		a;
	long	nb;

	nb = (long)n;
	a = 0;
	i = ft_compt(n, 0);
	if (!(dest = malloc(i + 1)))
		return (0);
	if (n < 0)
	{
		a++;
		nb *= -1;
		dest[0] = '-';
	}
	while (a != i)
	{
		dest[a] = (char)(ft_chifre(nb, a + 1, i) + 48);
		a++;
	}
	dest[a] = 0;
	return (dest);
}
