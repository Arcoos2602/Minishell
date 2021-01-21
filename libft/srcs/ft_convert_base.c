/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:25:50 by gbabeau           #+#    #+#             */
/*   Updated: 2020/02/04 15:59:19 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	verification(char *base)
{
	unsigned int	a;
	unsigned int	compt;

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

static void			ft_putnbr_base(char **s, int nbr, char *base, int taill)
{
	unsigned int	nb;
	unsigned int	bs;
	unsigned int	i;

	i = 0;
	bs = 0;
	bs = verification(base);
	nb = nbr;
	if (bs != 0)
	{
		if (nb / bs != 0)
			ft_putnbr_base(s, nb / bs, base, taill + 1);
		if (nb / bs == 0)
			*s = malloc(sizeof(**s) * (taill + 2));
		if (nb < 0)
		{
			nb = nb * -1;
			s[0][0] = '-';
			taill++;
		}
		s[0][taill] = base[nb % bs];
		if (nb / bs == 0)
			s[0][taill + 1] = '\0';
	}
}

static void			ft_rev_char_tab_case(char *tab, unsigned int n,
						unsigned int size, unsigned int start)
{
	char	t;

	t = tab[size - n - start];
	tab[size - n - start] = tab[n];
	tab[n] = t;
}

static void			ft_rev_char_tab(char *tab)
{
	unsigned int		size;
	unsigned int		n;

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

char				*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char				*s1;
	unsigned int		a;
	unsigned int		b;

	b = 0;
	if (0 == verification_atoi(base_from))
		return (NULL);
	if (0 == verification(base_to))
		return (NULL);
	a = ft_atoi_base(nbr, base_from);
	ft_putnbr_base(&s1, a, base_to, 0);
	ft_rev_char_tab(s1);
	free(nbr);
	return (s1);
}
