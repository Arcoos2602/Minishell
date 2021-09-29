/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:49:55 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/29 09:03:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	get_next_line(char **line, int i)
{
	int		ret;
	char	buf;

	ret = read(0, &buf, 1);
	if (ret == -1)
		return (-1);
	if (ret == 1 && buf != '\n')
	{
		ret = get_next_line(line, i + 1);
		if (ret == -1)
			return (-1);
		(*line)[i] = buf;
	}
	else
	{
		(*line) = (char *)malloc(sizeof(char) * (i + 1));
		if (!(*line))
			return (-1);
		(*line)[i] = '\0';
	}
	return (ret);
}
