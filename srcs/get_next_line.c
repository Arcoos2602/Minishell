/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2019/10/24 14:53:59 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 12:33:14 by gbabeau          ###   ########.fr       */
=======
/*   Created: 2019/10/21 14:49:55 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:44:28 by tcordonn         ###   ########.fr       */
>>>>>>> 7b219635d73c71bf978e2acac53470d94453e7c8
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
<<<<<<< HEAD
		line2 = malloc(i + 1);
		if (!line2)
			return (NULL);
		line2[i] = '\0';
		ft_memcpy(line2, buffer, size);
		return (line2);
=======
		*line = ft_substr(str, 0, len);
		tmp = ft_strdup(&str[len + 1]);
		free(str);
		str = tmp;
>>>>>>> 7b219635d73c71bf978e2acac53470d94453e7c8
	}
	else
	{
		*line = ft_substr(str, 0, len);
		free(str);
		str = NULL;
		return (0);
	}
<<<<<<< HEAD
	return (line2);
}

int	ft_line(char *c)
{
	int	a;

	a = ft_strlen(c);
	if (c != 0)
		if (ft_buffer_size_char(c) == a)
			return (2);
=======
>>>>>>> 7b219635d73c71bf978e2acac53470d94453e7c8
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
<<<<<<< HEAD
	  		if (check_read == 0)
				return (0);
			c = copy(c, buffer, check_read);
			if ((c != 0) && (check_read <= 0 || BUFFER_SIZE > check_read))
				return (ft_line_copy(0, &(*line), &c, buffer));
			else if ((c != 0) && 1 == (check_read = ft_line(c)))
				return (ft_line_copy(1, &(*line), &c, buffer));
=======
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
>>>>>>> 7b219635d73c71bf978e2acac53470d94453e7c8
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (ft_return(str, line, ret, fd));
}
