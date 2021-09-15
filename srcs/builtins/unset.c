/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:30:52 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 17:39:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

char	**new_env_del(char **env, char *to_delete, int size)
{
	char	**new;
	int		i;
	int		x;
	int		j;

	i = 0;
	x = 0;
	new = malloc(sizeof(char *) * (size + 1));

	while (env[x] != NULL)
	{
		j = 0;
		while (env[x][j] != '=')
        	j++;
		if (ft_strncmp(to_delete, env[x], j) != 0)
		{
			new[i] = ft_strdup(env[x]);
			i++;
		}
		free(env[x]);
		x++;
	}
	new[i++] = NULL;
		free(env);
	return (new);
}

int compare_var(char *env, char *var, int i)
{
    int		j;
    j = 0;
    
    while (env[j] != '=')
        j++;
    if (ft_strncmp(var, env, j + i) == 0)
		return (1);
    return (0);
}

char 	**env_delete(char **env, char  *var) // recreer env avec un en -
{
	int		i;
	int		new;

  	i = -1;
	new = 0;
    while (env[++i] != NULL)
	{
		if(compare_var(env[i], var, 0) == 1)
            new = 1;

    }
	if (new == 1)
	{
		env = new_env_del(env, var, i);
	}
	return (env);
}

int ft_check_var_unset(char *var)
{
    int i;

    i = 0;
    if (ft_compare_c_to_s(var[i],"0123456789="))
        return (0);
    while (var[++i] != '\0')
    {
        if (ft_compare_c_to_s(var[i],"="))
                return (0);
    }
    return (1);
}

char    **ft_unset(t_pipes *pipes, char **env)
{
    int i;

    i = 0;

	while (pipes->command[++i] != NULL)
    {
        if (ft_check_var_unset(pipes->command[i]))
    	    env = env_delete(env, pipes->command[i]);
        else
        {
            ft_putstr_fd("ERROR\n",2);
            g_global = 1;
        }
    }
	return (env);
}