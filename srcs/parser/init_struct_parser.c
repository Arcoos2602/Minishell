/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:26:51 by gbabeau           #+#    #+#             */
/*   Updated: 2021/03/05 14:30:45 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

t_parser	*add_parser(t_parser *parser, t_parser *next)
{
	if (parser == NULL)
		parser = next;
	if (parser->next == NULL)
		parser->next = next;
	else
		add_parser(parser->next, next);
	return (next);
}

t_parser	*parser_new(char **lexer, int *i)
{
	t_parser	*parser;

	if (0 == (parser = malloc(sizeof(t_parser))))
		return (NULL);
	parser->pipe = NULL;
	parser->next = NULL;
	if (0 == (parser->pipe = init_pipes(lexer, i)))
		return (NULL);
	return (parser);
}

t_parser	*init_parser(char **lexer, int *i)
{
	int			nbr;
	t_parser	*parser;

	*i = 0;
	parser = NULL;
	if (lexer == NULL)
			return (NULL);
	nbr = nbr_command_line(lexer);
	//printf("nombre command  = %d\n", nbr);
	while (nbr != 0)
	{
		if (parser == NULL)
		{
			if (0 == (parser = parser_new(lexer, i)))
				return (NULL);
		}
		else if (0 == add_parser(parser, parser_new(lexer, i)))
			return (NULL);
		nbr--;
		if (nbr != 0)
		{
			while (lexer[*i][0] != ';')
				*i += 1;
			*i += 1;
		}
	}
	return (parser);
}
