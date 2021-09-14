/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/05/06 13:38:44 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"


int ft_number(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (ft_isdigit(str[i++]) != 1)
			return (0);
	}
	return (1);
}

void		ft_exit(t_pipes *pipes)
{
	if (pipes->command[1] == NULL)
		exit(EXIT_SUCCESS);
	if (pipes->command[2] == NULL)
	{
		if (ft_number(pipes->command[1]) == 1)
				exit(ft_atoi(pipes->command[1]));
		else
		{
		ft_putstr_fd("ERROR\n",2);
		exit(2);
		}
	}
	if (ft_number(pipes->command[1]) == 1)
			ft_putstr_fd("ERROR\n",2);
	else
	{
		ft_putstr_fd("ERROR\n",2);
		exit(2);
	}
}
char	*ft_strjoin_cd(char const *s1, char const *s2)
{
	int		tail1;
	int		tail2;
	char	*dst;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	tail1 = ft_strlen((char*)s1);
	tail2 = ft_strlen((char*)s2);
	if (!(dst = malloc(tail1 + tail2 + 1)))
		return (0);
	tail1 = 0;
	tail2 = 0;
	while (s1[tail1] != '\0')
	{
		dst[tail1] = s1[tail1];
		tail1++;
	}
	while (s2[tail2] != '\0')
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
	return (dst);
}

void    ft_cd(char	*str, char **env)
{
	int a;
	int		x;
	int		j;
	char late[1000];


	a = chdir(str);
	if ( a == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
	}
	else
	{
	x = 0;
	while (env[x] != NULL)
	{
		j = 0;
		while (env[x][j] != '=')
        	j++;
		if (ft_strncmp("PWD=", env[x], j) == 0)
		{
			free(env[x]);
			env[x] = ft_strjoin_cd("PWD=", getcwd(late,1000));
		}
		x++;
	}
	}
	getcwd(env[0], 555);
	printf("%s\n", env[0]);
	//exit(EXIT_SUCCESS);
}

char 	*ft_getenv(char **paths, char *var)
{
	int		x;
	int		j;

	x = 0;

	while (paths[x] != NULL)
	{
		j = 0;
		while (paths[x][j] != '=')
        	j++;
		if (ft_strncmp(var, paths[x], j) == 0)
			return (&paths[x][j+1]);
		x++;
	}
	return (" ");
}

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

char 	**env_delete(char **env, char  *var) // recreer env avec un en -
{
	int		i;
  	int		j;
	int		new;

  	i = -1;
	new = 0;
    while (env[++i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
        	j++;
      	if (ft_strncmp(var, env[i], j) == 0)
		  {
				new++;
		  }
    }
	if (new == 1)
	{
		env = new_env_del(env, var, i);
	}
	return (env);
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

char    **ft_unset(t_pipes *pipes, char **env)
{
	if (pipes->command[1] != NULL)
    	env = env_delete(env, pipes->command[1]);
	return (env);
}

int		check_builtins(t_pipes	*pipes, t_path *path, char **env)
{
	if (ft_strncmp(pipes->command[0], "exit", 4) == 0)
		ft_exit(pipes);
	else if (ft_strncmp(pipes->command[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(pipes->command[0], "pwd", 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp(pipes->command[0], "echo", 3) == 0)
		ft_echo(pipes);
  	else if (ft_strncmp(pipes->command[0], "export", 6) == 0)
		env = ft_export(pipes, env);
	else if (ft_strncmp(pipes->command[0], "unset", 5) == 0)
		env = ft_unset(pipes, env);
	else if (ft_strncmp(pipes->command[0], "cd", 2) == 0)
		ft_cd(pipes->command[1], env);
	else 
		return (0);
	path->path = env;
	return (1);
}
