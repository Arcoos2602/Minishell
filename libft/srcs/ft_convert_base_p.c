/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:25:50 by gbabeau           #+#    #+#             */
/*   Updated: 2020/01/30 11:50:42 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long int	verification(char *base)
{
	unsigned long int	a;
	unsigned long int	compt;

	a = 0;
	compt = 0;
	while (base[a] != '\0')
	{
		while (base[compt] != '\0')
		{
			if (base[compt] == base[a] && compt != a)
				return (0);
			compt++;
		}
		compt = 0;
		if ((base[a] < 32 || base[a] > 126
			|| base[a] == '-' || base[a] == '+') && base[a] != '\0')
			return (0);
		a++;
	}
	if (a > 1)
		return (a);
	return (0);
}

static void					ft_putnbr_base(char **s, unsigned long int nbr,
									char *base, unsigned long int taill)
{
	unsigned long int	nb;
	unsigned long int	bs;
	unsigned long int	i;

	i = 0;
	bs = 0;
	bs = verification(base);
	nb = nbr;
	if (bs != 0)
	{
		if (nb / bs != 0)
			ft_putnbr_base(s, nb / bs, base, taill + 1);
		if (nb / bs == 0)
		{
			*s = malloc(sizeof(**s) * (taill + 2));
			s[0][taill + 1] = '\0';
		}
		if (nb < 0)
		{
			nb = nb * -1;
			s[0][0] = '-';
			taill++;
		}
		s[0][taill] = base[nb % bs];
	}
}

static void					ft_rev_char_tab_case(char *tab, unsigned long int n,
								unsigned long int size, unsigned long int start)
{
	char	t;

	t = tab[size - n - start];
	tab[size - n - start] = tab[n];
	tab[n] = t;
}

static void					ft_rev_char_tab(char *tab)
{
	unsigned long int		size;
	unsigned long int		n;

	size = 0;
	while (tab[size])
		size++;
	size++;
	n = 0;
	if (tab[0] != '-')
		while (n < size / 2)
		{
			ft_rev_char_tab_case(tab, n, size, 2);
			n++;
		}
	else
	{
		n++;
		while (n < size / 2)
		{
			ft_rev_char_tab_case(tab, n, size, 1);
			n++;
		}
	}
}

char						*ft_convert_base_p(char *nbr, char *base_from,
								char *base_to)
{
	char					*s1;
	unsigned long int		a;
	unsigned long int		b;

	b = 0;
	if (0 == verification_atoi_p(base_from))
		return (NULL);
	if (0 == verification(base_to))
		return (NULL);
	a = ft_atoi_base_p(nbr, base_from);
	ft_putnbr_base(&s1, a, base_to, 0);
	ft_rev_char_tab(s1);
	free(nbr);
	return (s1);
}
