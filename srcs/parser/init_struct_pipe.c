/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:26:38 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/08 15:46:33 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

t_redi *init_new_redi(t_redi *redi, char **lexer)
{
	if (lexer[0][0]== '<')
	redi->type = 0;
	else if (lexer[0][1] == '\0')
	redi->type = 1;
	else
	redi->type = 2;
		redi->put = ft_strdup(lexer[1]);
	return redi;
}

t_redi	*redi_new(char **lexer)
{
	t_redi	*new;

	if (0 == (new = malloc(sizeof(t_redi))))
		return (NULL);
	new->next = NULL;
	return (init_new_redi(new, lexer));
}

t_redi		*add_redi(t_redi *redi, t_redi *next)
{
	if (redi == NULL)
		redi = next;
	else if (redi->next == NULL)
		redi->next = next;
	else
		add_redi(redi->next, next);
	return (next);
}


t_redi	*init_put(t_redi *redi, char **lexer, int *i)
{
	int	deb;

	deb = 0;
	while (lexer[*i + deb] != NULL && 0 == ft_compare_c_to_s(lexer[*i + deb][0],"|;"))
	{
		if (ft_compare_c_to_s(lexer[*i + deb][0],"><"))
			redi = add_redi(redi, redi_new(&lexer[*i + deb]));
		deb++;
	}
	return (redi);
}

static int nbr_redi(char **lexer)
{
	int n;
	int i;

	n = -1;
	i = 0;

	while (lexer[++n] != NULL && 0 == ft_compare_c_to_s(lexer[n][0],"|;"))
	{
		if( 1 == ft_compare_c_to_s(lexer[n][0],"><"))
			i++;
	}
	return (i);
}

t_pipes		*add_pipe(t_pipes *pipe, t_pipes *next)
{
	if (pipe == NULL)
		pipe = next;
	else if (pipe->next == NULL)
		pipe->next = next;
	else
		add_pipe(pipe->next, next);
	pipe->output = 0;
	return (next);
}

t_pipes		*init_new(t_pipes *new, char **lexer, int *i)
{
	new->command = init_command_pipe(new->command, lexer, i);
	if (0 != nbr_redi(&lexer[*i]))
	{
		if (0 == (new->redi = init_put(new->redi, lexer, i)))
			return (NULL);
	}
	return (new);
}

t_pipes		*pipe_new(char **lexer, int *i)
{
	t_pipes	*new;

	if (0 == (new = malloc(sizeof(t_pipes))))
		return (NULL);
	new->next = NULL;
	new->redi = NULL;
	return (init_new(new, lexer, i));
}

t_pipes		*init_pipes(char **lexer, int *i)
{
	int		nbr;
	t_pipes	*pipe;

	pipe = NULL;
	nbr = words_command(lexer, *i);
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
