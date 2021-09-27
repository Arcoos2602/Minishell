/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:49:55 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:44:28 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int		ft_struct(char *str, char **line)
{
	char	*tmp;
	int		len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (str[len] == '\n')
	{
		*line = ft_substr(str, 0, len);
		tmp = ft_strdup(&str[len + 1]);
		free(str);
		str = tmp;
	}
	else
	{
		*line = ft_substr(str, 0, len);
		free(str);
		str = NULL;
		return (0);
	}
	return (1);
}

int		ft_return(char *str, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if ((ret == 0 && str == NULL))
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (ft_struct(&str[fd], line));
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	char		*tmp;

	if (BUFFER_SIZE <= 0)
		return (-1);
	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (str == NULL)
			str = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (ft_return(str, line, ret, fd));
}
