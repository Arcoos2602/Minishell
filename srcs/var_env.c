/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:55:39 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/30 10:18:43 by user42           ###   ########.fr       */
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
		path[i++] = ft_strdup(env[n]);
	path[i] = NULL;
	return (path);
}
