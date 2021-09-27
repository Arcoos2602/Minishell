/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:17:08 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 09:58:07 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

char	*ft_strjoin2(char const *s1, char const *s2, int size)
{
	int		tail1;
	int		tail2;
	char	*dst;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	tail1 = ft_strlen((char*)s1);
	tail2 = size;
	if (!(dst = malloc(tail1 + tail2 + 1)))
		return (0);
	tail1 = 0;
	tail2 = 0;
	while (s1[tail1] != '\0')
	{
		dst[tail1] = s1[tail1];
		tail1++;
	}
	while (tail2 != size)
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
	return (dst);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*a;
	const char	*b;

	a = dest;
	b = src;
	if (!src || !dest)
		return (0);
	while (n--)
		*a++ = *b++;
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;
	long			n;
	unsigned char	*point;

	n = (long)(nmemb * size);
	if (!(s = malloc(n)))
		return (0);
	point = s;
	while (n--)
		*point++ = '\0';
	return (s);
}

int		ft_buffer_size_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
