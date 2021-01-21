/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:25:01 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/13 17:25:03 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		tail1;
	int		tail2;
	char	*dst;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	tail1 = ft_strlen((char*)s1);
	tail2 = ft_strlen((char*)s2);
	if (!(dst = malloc(tail1 + tail2 + 1)))
		return (0);
	tail1 = 0;
	tail2 = 0;
	while (s1[tail1] != '\0')
	{
		dst[tail1] = s1[tail1];
		tail1++;
	}
	while (s2[tail2] != '\0')
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
	return (dst);
}
