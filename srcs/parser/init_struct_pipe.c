/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:30:09 by gbabeau           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/25 12:59:30 by gbabeau          ###   ########.fr       */
=======
/*   Updated: 2021/02/25 11:43:25 by tcordonn         ###   ########.fr       */
>>>>>>> 28e0ac27f423a01e061e60607b8fcdc4dd8f6bae
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

t_pipe		*init_put(t_pipe *new, char **lexer, int *i)
{
	int	deb;

	deb = *i;
	if (NULL == (new->input = init_input(new->input, &lexer[deb], deb)))
		return (NULL);
	if (NULL == init_output(new, &lexer[deb], deb))
		return (NULL);
	return (new);
}

t_pipe		*add_pipe(t_pipe *pipe, t_pipe *next)
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

t_pipe		*init_new(t_pipe *new, char **lexer, int *i)
{
	if (NULL == (new->command = init_command_pipe(new->command, lexer, i)))
		return (NULL);
	if (0 == init_put(new, lexer, i))
		return (NULL);
	return (new);
}

t_pipe		*pipe_new(char **lexer, int *i)
{
	t_pipe	*new;

	if (0 == (new = malloc(sizeof(t_pipe))))
		return (NULL);
	new->next = NULL;
	return (init_new(new, lexer, i));
}

t_pipe		*init_pipe(char **lexer, int *i)
{
	int		nbr;
	t_pipe	*pipe;

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
