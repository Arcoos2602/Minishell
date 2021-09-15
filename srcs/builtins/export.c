/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 15:31:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

char	**new_env_exp(char **env, char *to_add, int size)
{
	char	**new;
	int		x;

	x = 0;

	new = malloc(sizeof(char *) * (size + 2));

	while (env[x] != NULL)
	{
			new[x] = ft_strdup(env[x]);
			free(env[x]);
			x++;
	}
	new[x++] = ft_strdup(to_add);
	new[x++] = NULL;
		free(env);
	return (new);
}

char   **env_add(char **env, char  *var) // recreer env avec un en +
{
	int i;
		i = -1;
	if (ft_compare_c_to_s('=', var))
	{
	while (env[++i] != NULL)
	;
		env = new_env_exp(env, var, i);
	}
	return (env);
}

char   **ft_export(t_pipes *pipes, char **env)
{
	int i;

	i = 1;
	while (pipes->command[i] != NULL)
    	env = env_add(env, pipes->command[i++]);
	return env;
}