/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:29:43 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/11 13:47:27 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*cp;

	i = 0;
	while (src[i] && i < n)
		i++;
	if (!(cp = malloc(sizeof(*cp) * i + 1)))
		return (0);
	i = 0;
	while (src[i] && i < n)
	{
		cp[i] = src[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
