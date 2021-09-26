/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:10:07 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/26 20:49:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

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

void ft_cd(t_pipes *pipes, char **env)
{
	int a;
	int		x;
	int		j;
	char	*buff;
	char 	late[1000];

 if ( pipes->command[1] == NULL || pipes->command[2] == NULL)
	{
		if (pipes->command[1] == NULL)
		{
			buff = ft_getenv(env, "HOME");
			if (buff == NULL)
			{
				ft_putstr_fd("bash : cd: \"HOME\" is not set\n", 2);
				return;
			}
				a = chdir(buff);
				printf("%d et %s\n",a,buff);
		}
		else
			a = chdir(pipes->command[1]);
	
		if (a == -1)
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
	}
	else
		ft_putstr_fd("bash : cd: too much arguments\n", 2);
	getcwd(env[0], 555);
	printf("%s\n", env[0]);
}