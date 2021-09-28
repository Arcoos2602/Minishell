/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:35:25 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/28 13:47:56 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

t_pipes	*add_pipe(t_pipes *pipe, t_pipes *next)
{
	if (pipe == NULL)
		pipe = next;
	else if (pipe->next == NULL)
		pipe->next = next;
	else
		add_pipe(pipe->next, next);
	pipe->put[1] = -1;
	pipe->put[0] = -1;
	pipe->error = 0;
	pipe->exe = 0;
	return (next);
}

int	ft_check_builtin_parser(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	return (0);
}

t_pipes	*init_new(t_pipes *new, char **lexer, int *i, t_path *paths)
{
	new->command = init_command_pipe(new->command, lexer, i, paths);
	if (new->command != NULL && new->command[0] != NULL)
		new->builtin = ft_check_builtin_parser(new->command[0]);
	if (0 != nbr_redi(&lexer[*i]))
	{
		new->redi = init_put(new->redi, lexer, i, paths);
		if (0 == new->redi)
			return (NULL);
	}
	return (new);
}

t_pipes	*pipe_new(char **lexer, int *i, t_path *paths)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (NULL == new)
		return (NULL);
	new->builtin = 0;
	new->next = NULL;
	new->redi = NULL;
	return (init_new(new, lexer, i, paths));
}

t_pipes	*init_pipes(char **lexer, int *i, t_path *paths)
{
	int		nbr;
	t_pipes	*pipe;

	pipe = NULL;
	nbr = words_command(lexer, *i);
	while (nbr--)
	{
		if (pipe == NULL)
		{
			pipe = pipe_new(lexer, i, paths);
			if (pipe == NULL)
				return (NULL);
		}
		else if (0 == (add_pipe(pipe, pipe_new(lexer, i, paths))))
			return (NULL);
		if (nbr != 0)
		{
			while (lexer[*i][0] != '|')
				*i += 1;
			*i += 1;
		}
	}
	return (pipe);
}
