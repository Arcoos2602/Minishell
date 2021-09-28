/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:55:39 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/28 16:36:36 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

char	**env_malloc(char **path, char **env)
{
	int	n;
	int	i;

	n = -1;
	while (env[++n] != NULL)
		;
	path = malloc((n + 1) * sizeof(char *));
	if (path == NULL)
		return (NULL);
	i = 0;
	n = -1;
	while (env[++n] != NULL)
	{
		path[i++] = ft_strdup(env[n]);
	}
	path[i] = NULL;
	return (path);
}

void	replace_quotes(char *dest, char *buf, int *i, int *cpt)
{
	while (buf[*i] != '\0')
	{
		dest[*i + *cpt] = buf[*i];
		if (buf[*i] == '\'')
		{
			dest[*i] = '\'';
			dest[*i + ++*cpt] = '"';
			dest[*i + ++*cpt] = '\'';
			dest[*i + ++*cpt] = '"';
			dest[*i + ++*cpt] = '\'';
		}
		++*i;
	}
	dest[*i + *cpt] = '\0';
}

void	finish_env_line(char *str, char *end, char *buf)
{
	int	nbr;

	nbr = 0;
	free(str);
	free(end);
	while (buf[nbr] != NULL)
		free(buf[nbr++]);
	free(buf);
}

char	*line_env(char *str, t_path *path)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{		
		if (ft_compare_c_to_s(str[i], "'\"") == 1)
		{
			if (str[i] == '"')
			{	
				while (str[i] != '\0' && str[++i] != '"')
					;
			}
			else if (str[i] == '\'')
			{
				while (str[i] != '\0' && str[++i] != '\'')
					;
			}
		}
		else if (str[i] == '$')
			str = add_env_line(str, &i, path);
		else
			i++;
	}
	return (str);
}
