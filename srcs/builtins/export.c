/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 20:13:40 by user42           ###   ########.fr       */
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

int ft_test_new_env(char *var)
{
	int a;

	a = 0;
	while(var[a] != '\0' && var[a] != '=')
	{
		if (ft_compare_c_to_s(var[a++],"\"'?$|<>"))
		{
			ft_putstr_fd("ERROR:",2);
			ft_putstr_fd(var,2);
			ft_putstr_fd("\n",2);
			return (1);
		}
	}
	return (0);
}

char   **env_add(char **env, char  *var, t_path *path) // recreer env avec un en +
{
	int i;
	int j;
	int x;

		x = 0;
		i = -1;
		if (ft_test_new_env(var))
			return (env);
	if (ft_getenv(path->path, var) == NULL && ft_compare_c_to_s('=', var))
	{
		while (env[++i] != NULL)
		;
		env = new_env_exp(env, var, i);
		
	}
	else if (ft_getenv(path->path, var) != NULL && ft_compare_c_to_s('=', var))
	{
		while (env[x] != NULL)
		{
		j = 0;
		while (env[x][j] != '=')
        	j++;
		if (ft_strncmp(var, env[x], j) == 0)
			env[x] = ft_strdup(var);
		x++;
		}	
	}
	return (env);
}


int ft_print_env_2(char **env, char *str , int i)
{
	int n;
	int pos;
	int size;

	n = 0;
	pos = 0;
	size = ft_strlen(str);
	while (env[n] != NULL)
	{
		if (ft_strncmp(str, env[n], size) > 0)
			pos++;
		n++;
	}
	if (pos == i)
		return (1);
	return (0);
}


int ft_compte_env(char *str)
{
	int i;

	i = 0;
	while(str != NULL && str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

void ft_print_env_3(char *str)
{
	int n;

	n = ft_compte_env(str) ;
	write(1,"export " ,7);
	write(1,str,n+1);
	write(1,"\"",1);
	write(1, &str[n+1], ft_strlen(&str[n+1]));
	write(1,"\"\n", 2);
}


void ft_print_env_alp(char **env)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (env[i] != NULL)
	{
		while (env[nbr] != NULL)
		{
			if (ft_print_env_2(env, env[nbr] ,i))
			ft_print_env_3(env[nbr]);
		nbr++;
		}
		i++;
		nbr = 0;
	}
}

char   **ft_export(t_pipes *pipes, char **env, t_path *path)
{
	int i;

	i = 1;
	if (pipes->command[i] == NULL)
	{
		ft_print_env_alp(env);
		return (env);
	}
	while (pipes->command[i] != NULL)
    	env = env_add(env, pipes->command[i++], path);
	return env;
}