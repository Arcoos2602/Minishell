/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:53:59 by gbabeau           #+#    #+#             */
/*   Updated: 2021/04/07 15:15:07 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

char	*copy(char *c, char *buffer, int size)
{
	int		i;
	char	*line2;

	i = size;
	if (c == 0)
	{
		if (!(line2 = malloc(i + 1)))
			return (NULL);
		line2[i] = '\0';
		ft_memcpy(line2, buffer, size);
		return (line2);
	}
	else
	{
		line2 = ft_strjoin2(c, buffer, size);
		free(c);
		c = 0;
	}
	return (line2);
}

int		ft_line(char *c)
{
	if (c != 0)
		if (ft_buffer_size_char(c) == ft_strlen(c))
			return (2);
	return (1);
}

char	*c_finish(char **c)
{
	char	*line2;
	int		i;
	int		n;

	line2 = "12";
	if (*c != 0 && (ft_buffer_size_char(*c) != (n = ft_strlen(*c))))
	{
		i = n - ft_buffer_size_char(*c) + 1;
		if (!(line2 = malloc(i)))
			return (NULL);
		line2[--i] = '\0';
		while (i--)
			line2[i] = (*c)[n--];
		free(*c);
		*c = line2;
	}
	else
	{
		if (*c != 0)
			free(*c);
		*c = 0;
	}
	return (line2);
}

int		ft_line_copy(int a, char **line, char **c, char *buffer)
{
	int	i;

	if (*c != 0)
		i = ft_buffer_size_char(*c) + 1;
	else
		i = 1;
	if (!(*line = malloc(i)))
		return (-1);
	(*line)[--i] = '\0';
	while (i-- != 0)
		(*line)[i] = (*c)[i];
	if (0 == c_finish(&(*c)))
		return (-1);
	free(buffer);
	if (a == 1 || *c != 0)
		return (1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*c = 0;
	int			check_read;
	char		*buffer;

	check_read = 2;
	if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = ft_calloc(BUFFER_SIZE + 1, 1))
		|| line == 0)
		return (-1);
	while (check_read == 2)
		if (c != 0 && 1 >= (ft_line(c)))
		{
			return (ft_line_copy(1, &(*line), &c, buffer));
		}
		else if (0 <= (check_read = read(fd, buffer, BUFFER_SIZE)))
		{
      if (check_read == 0)
      {
        ft_putstr_fd("exit\n", 1);
		    exit(EXIT_SUCCESS);
      }
			c = copy(c, buffer, check_read);
			if ((c != 0) && (check_read <= 0 || BUFFER_SIZE > check_read))
				return (ft_line_copy(0, &(*line), &c, buffer));
			else if ((c != 0) && 1 == (check_read = ft_line(c)))
				return (ft_line_copy(1, &(*line), &c, buffer));
		}
	free(buffer);
	if (c != 0)
		free(c);
	return (-1);
}
