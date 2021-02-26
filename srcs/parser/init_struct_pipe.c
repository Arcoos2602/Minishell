/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:26:38 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/26 12:26:45 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

t_pipes		*init_put(t_pipes *new, char **lexer, int *i)
{
	int	deb;

	deb = *i;
	if (NULL == (new->input = init_input(new->input, &lexer[deb], deb)))
		return (NULL);
	if (NULL == init_output(new, &lexer[deb], deb))
		return (NULL);
	return (new);
}

t_pipes		*add_pipe(t_pipes *pipe, t_pipes *next)
{
//	printf("{{%s}}\n",next->command[0]);
	if (pipe == NULL)
		pipe = next;
	else if (pipe->next == NULL)
		pipe->next = next;
	else
		add_pipe(pipe->next, next);
	return (next);
}

t_pipes		*init_new(t_pipes *new, char **lexer, int *i)
{
	if (NULL == (new->command = init_command_pipe(new->command, lexer, i)))
		return (NULL);
	if (0 == init_put(new, lexer, i))
		return (NULL);
	return (new);
}

t_pipes		*pipe_new(char **lexer, int *i)
{
	t_pipes	*new;

	if (0 == (new = malloc(sizeof(t_pipes))))
		return (NULL);
	new->next = NULL;
	return (init_new(new, lexer, i));
}

t_pipes		*init_pipes(char **lexer, int *i)
{
	int		nbr;
	t_pipes	*pipe;

	pipe = NULL;
	nbr = words_command(lexer, *i);
	//printf("nombre pipe = %d\n", nbr);
	while (nbr--)
	{
		if (pipe == NULL)
		{
			if (0 == (pipe = pipe_new(lexer, i)))
				return (NULL);
		}
		else if (0 == (add_pipe(pipe, pipe_new(lexer, i))))
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
