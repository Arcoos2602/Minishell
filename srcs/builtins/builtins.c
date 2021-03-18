/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/15 13:31:58 by tcordonn         ###   ########.fr       */
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

void		ft_cd(char	*str)
{
	char	current[555];

	getcwd(current, 555);
	printf("%s\n", current);
	if (chdir("..") == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
	}
	getcwd(current, 555);
	printf("%s\n", current);
	exit(EXIT_SUCCESS);
}

void		check_builtins(t_pipes	*pipes, char **path)
{
	if (ft_strncmp(pipes->command[0], "exit", 4) == 0)
		ft_exit(pipes);
	if (ft_strncmp(pipes->command[0], "env", 4) == 0)
		ft_env(path);
	if (ft_strncmp(pipes->command[0], "pwd", 3) == 0)
		ft_pwd(path);
	if (ft_strncmp(pipes->command[0], "echo", 3) == 0)
		ft_echo(pipes, path);
	if (ft_strncmp(pipes->command[0], "cd", 6) == 0)
		ft_cd(pipes->command[0]);
	/*if (ft_strncmp(pipes->command[0], "cd", 2) == 0)
		ft_cd(pipes);*/
}
