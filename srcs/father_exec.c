/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:42:17 by thomas            #+#    #+#             */
/*   Updated: 2021/09/28 00:43:58 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	comand_not_found(t_pipes *pipes, t_path *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pipes->command[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
	ft_free(path->parser, path);
	exit(127);
}

int	ft_execve(char *s1, char *s2, char **command, char **env)
{
	char	*dst;
	int		tail1;
	int		tail2;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	tail1 = -1;
	tail2 = 0;
	while (s1[++tail1] != '\0')
		dst[tail1] = s1[tail1];
	dst[tail1++] = '/';
	while (s2[tail2] != '\0')
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
	execve(dst, &command[0], env);
	free(dst);
	return (0);
}

void	ft_excve_2(t_pipes *pipes, t_path *path)
{
	DIR		*test;

	test = opendir(pipes->command[0]);
	if (test != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(": est un dossier\n", 2);
		closedir(test);
		ft_free(path->parser, path);
		exit(126);
	}
	execve(pipes->command[0], &pipes->command[0], path->path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pipes->command[0], 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_putnbr_fd(errno, 2);
	ft_free(path->parser, path);
	if (errno == 2)
		exit(127);
	exit(126);
}
