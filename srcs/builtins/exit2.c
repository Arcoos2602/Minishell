/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:41:48 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 15:46:55 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	compare(char *str, int size, int neg)
{
	if (size > 19)
		return (-1);
	if (size == 19)
	{
		if (neg == 0 && ft_strncmp(str, "9223372036854775808", 19) >= 0)
			return (-1);
		if (neg == 1 && ft_strncmp(str, "9223372036854775809", 19) >= 0)
			return (-1);
	}
	return (1);
}

int	is_valid(char *str)
{
	int	i;
	int	size;
	int	neg;

	neg = 0;
	i = 0;
	if (str[i] == '-')
	{
		neg++;
		i++;
	}
	while (str[i] == '0')
		i++;
	size = ft_strlen(&str[i]);
	if (compare(&str[i], size, neg) == -1)
		return (-1);
	return (1);
}
