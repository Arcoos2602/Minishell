/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:41:57 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/28 13:48:03 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

static int	nbr_redi(char **lexer)
{
	int	n;
	int	i;

	n = -1;
	i = 0;
	while (lexer[++n] != NULL && 0 == ft_compare_c_to_s(lexer[n][0], "|;"))
	{
		if (1 == ft_compare_c_to_s(lexer[n][0], "><"))
			i++;
	}
	return (i);
}

char	*ft_buff_null(char *line, int cpt, int i)
{
	char	*dest;

	dest = malloc(ft_strlen(line) + cpt + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, line, i - cpt);
	ft_strlcpy(&dest[i - cpt - 1], &line[i], ft_strlen(&line[i]) + 1);
	return (dest);
}

char	*ft_buff_no_null(char *line, int cpt, int i, char *buff)
{
	char	*dest;

	dest = malloc(ft_strlen(line) + cpt + 2 + ft_strlen(buff));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, line, i - cpt);
	ft_strlcpy(&dest[i - cpt - 1], buff, ft_strlen(buff) + 1);
	ft_strlcpy(&dest[i + ft_strlen(buff) - cpt - 1],
		&line[i], ft_strlen(&line[i]) + 1);
	return (dest);
}

char	*ft_replace(char *line, t_path *path)
{
	char	*dest;
	char	*buff;
	int		i;
	int		cpt;
	char	*env;

	i = 0;
	dest = NULL;
	while (line != NULL && line[i] != '\0' && line[i] != '$')
		i++;
	if (line == NULL || line[i] == '\0')
		return (line);
	i++;
	cpt = ft_count(line, &i, "'$ \" | > <\n");
	env = ft_substr(line, i - cpt, cpt);
	buff = ft_getenv(path->path, env);
	if (buff != NULL)
		dest = ft_buff_no_null(line, cpt, i, buff);
	else
		dest = ft_buff_null(line, cpt, i);
	free(env);
	free(line);
	return (ft_replace(dest, path));
}	

char	*add_newline(char *line, t_path *path)
{
	char	*new_line;

	new_line = malloc(ft_strlen(line) + 2);
	ft_strlcpy(new_line, line, ft_strlen(line) + 1);
	new_line[ft_strlen(line)] = '\n';
	new_line[ft_strlen(line) + 1] = '\0';
	new_line = ft_replace(new_line, path);
	free(line);
	return (new_line);
}
