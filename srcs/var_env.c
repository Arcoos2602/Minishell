/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:55:39 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:20:05 by tcordonn         ###   ########.fr       */
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
	i = 0;
	n = -1;
	while (env[++n] != NULL)
		path[i++] = ft_strdup(env[n]);
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
	//printf("|%s|", str);
	return (str);
}
