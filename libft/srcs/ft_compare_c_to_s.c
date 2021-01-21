/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_c_to_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:39:48 by gbabeau           #+#    #+#             */
/*   Updated: 2020/10/08 15:01:40 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_compare_c_to_s(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		if (str[i++] == c)
			return (1);
	return (0);
}

int	ft_compare_s_to_s(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0')
		if (ft_compare_c_to_s(str1[i++], str2))
			return (1);
	return (0);
}
