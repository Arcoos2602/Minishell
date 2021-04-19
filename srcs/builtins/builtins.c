/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/04/19 15:25:43 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void		ft_exit(t_pipes *pipes)
{
	ft_putstr_fd("daw", 2);
	exit(EXIT_SUCCESS);
}

void    ft_cd(char	*str, char *env)
{
	getcwd(env, 555);
	printf("%s\n", env);
	if (chdir(str) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
	}
	getcwd(env, 555);
	printf("%s\n", env);
	//exit(EXIT_SUCCESS);
}

char	**new_env_del(char **env, char *to_delete, int size, int check)
{
	char	**new;
	int		i;
	int		x;
	int		j;

	i = 0;
	x = 0;
	new = malloc(sizeof(char *) * (size - 1));
	while (env[x] != NULL)
	{
		j = 0;
		while (env[x][j] != '=')
        	j++;
		//printf("%s\n", &env[x][j]);
		if (ft_strncmp(to_delete, env[x], j) != 0)
		{
			//printf("check");
			new[i] = ft_strdup(env[x]);
			printf("%s\n", new[i]);
			i++;
		}
		if (check != 0)
			free(env[x]);
		x++;
	}
	new[i++] = NULL;
	if (check != 0)
		free(env);
	return (new);
}

void	env_delete(char **env, char  *var) // recreer env avec un en -
{
	static 	int	check = 0;
	int		i;
    int		j;
	int		new;
	char	**env2;

    i = -1;
	new = 0;
    while (env[++i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
        	j++;
      	if (ft_strncmp(var, env[i], j) == 0)
			new++;
		//printf("%s\n", env[i]);
    }
	if (new == 1)
	{
		env = new_env_del(env, var, i, check);
		check++;
	}
	i = -1;
	while (env[++i] != NULL)
	{
		printf("env : %s\n", env[i]);
	}
}

void    env_add(char **env, char  *var) // recreer env avec un en +
{

}

int    ft_export(t_pipes *pipes, char **env)
{
	if (pipes->command[1] != NULL)
    	env_add(env, pipes->command[1]);
    exit(EXIT_SUCCESS);
}

int    ft_unset(t_pipes *pipes, char **env)
{
	if (pipes->command[1] != NULL)
    	env_delete(env, pipes->command[1]);
    exit(EXIT_SUCCESS);
}

char		*check_builtins(t_pipes	*pipes, char **env, char *useless)
{
	int		ret;

	ret = 0;
	if (ft_strncmp(pipes->command[0], "exit", 4) == 0)
		ft_exit(pipes);
	if (ft_strncmp(pipes->command[0], "env", 4) == 0)
		ft_env(env);
	if (ft_strncmp(pipes->command[0], "pwd", 3) == 0)
		ft_pwd(env);
	if (ft_strncmp(pipes->command[0], "echo", 3) == 0)
		ft_echo(pipes, env);
  	if (ft_strncmp(pipes->command[0], "export", 6) == 0)
		ft_export(pipes, env);
	if (ft_strncmp(pipes->command[0], "unset", 5) == 0)
		ft_unset(pipes, env);
	/*if (ft_strncmp(pipes->command[0], "cd", 6) == 0)
		ft_cd(pipes->command[1], env);*/
	/*if (ft_strncmp(pipes->command[0], "cd", 2) == 0)
		ft_cd(pipes);*/
}
