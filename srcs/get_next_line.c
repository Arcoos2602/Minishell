/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:49:55 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/28 00:31:26 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	ft_gnl_rec(char **line, int index)
{
	int		ret;
	char	buf;

	ret = read(0, &buf, 1);
	if (ret == -1)
		return (-1);
	if (ret == 1 && buf != '\n')
	{
		ret = ft_gnl_rec(line, index + 1);
		if (ret == -1)
			return (-1);
		(*line)[index] = buf;
	}
	else
	{
		(*line) = (char *)malloc(sizeof(char) * (index + 1));
		if (!(*line))
			return (-1);
		(*line)[index] = '\0';
	}
	return (ret);
}

int	get_next_line(char **line)
{
	return (ft_gnl_rec(line, 0));
}
