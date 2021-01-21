/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:32:39 by gbabeau           #+#    #+#             */
/*   Updated: 2020/01/30 11:50:51 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long int			verification_atoi_p(char *base)
{
	unsigned long int	nb;
	unsigned long int	compt;

	nb = 0;
	compt = 0;
	while (base[nb] != '\0')
	{
		while (base[compt] != '\0')
		{
			if (base[compt] == base[nb] && compt != nb)
				return (0);
			compt++;
		}
		compt = 0;
		nb++;
		if (((base[nb] >= 9 && base[nb] <= 13)
			|| (base[nb] == '-' || base[nb] == '+' || base[nb] == ' '))
				&& base[nb] != '\0')
			return (0);
	}
	return (nb);
}

static unsigned long int	signe(char *str, unsigned long int *nb)
{
	unsigned long int	i;
	unsigned long int	a;

	i = 1;
	a = 0;
	while (str[a] == ' ' || (str[a] >= 9 && 13 >= str[a]))
		a++;
	while (str[a] == '+' || str[a] == '-')
	{
		if (str[+a] == '-')
			i *= -1;
		a++;
	}
	*nb = a;
	return (i);
}

static unsigned long int	position(char str, char *base)
{
	unsigned long int	bs;

	bs = 0;
	while (base[bs] != str && base[bs] != '\0')
		bs++;
	return (bs);
}

unsigned long int			ft_atoi_base_p(char *str, char *base)
{
	unsigned long int	tail;
	unsigned long int	i;
	unsigned long int	nb;
	unsigned long int	renvoie;
	unsigned long int	bs;

	nb = 0;
	tail = verification_atoi(base);
	if (0 == tail)
		return (0);
	i = signe(str, &nb);
	bs = 0;
	renvoie = 0;
	while (bs < tail)
	{
		renvoie *= tail;
		renvoie = renvoie + bs;
		bs = position(str[nb], base);
		if (bs >= tail)
			return (i * renvoie);
		nb++;
	}
	return (i * renvoie);
}
