/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:25:01 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 01:29:37 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_join_copy(char *dst, char *s1, char *s2)
{
	int		tail1;
	int		tail2;

	tail1 = 0;
	tail2 = 0;
	while (s1 != 0 && s1[tail1] != '\0')
	{
		dst[tail1] = s1[tail1];
		tail1++;
	}
	while (s2 != 0 && s2[tail2] != '\0')
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		tail1;
	int		tail2;
	char	*dst;

	tail1 = 0;
	tail2 = 0;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	if (s1 != 0)
		tail1 = ft_strlen((char *)s1);
	if (s2 != 0)
		tail2 = ft_strlen((char *)s2);
	dst = malloc(tail1 + tail2 + 1);
	if (!dst)
		return (0);
	t_join_copy(dst, s1, s2);
	if (s1 != NULL)
		free(s1);
	return (dst);
}
