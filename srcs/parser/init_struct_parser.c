/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:26:51 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 13:19:50 by tcordonn         ###   ########.fr       */
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

t_parser	*parser_new(char **lexer, int *i, t_path *paths)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->pipe = NULL;
	parser->next = NULL;
	parser->pipe = init_pipes(lexer, i, paths);
	if (parser->pipe == NULL)
		return (NULL);
	return (parser);
}

static int	init_variable_p(char **lexer,int *nbr, int *i)
{
	*i = 0;
	if (lexer == NULL)
		return (0);
	*nbr = nbr_command_line(lexer);
	return (1);
}

t_parser	*init_parser(char **lexer, t_path *paths)
{
	int			nbr;
	t_parser	*parser;
	int			i;

	parser = NULL;
	if (0 == init_variable_p(lexer, &nbr, &i))
		return (NULL);
	while (nbr != 0)
	{
		if (parser == NULL)
		{
			parser = parser_new(lexer, &i, paths);
			if (0 == parser)
				return (NULL);
		}
		else if (0 == add_parser(parser, parser_new(lexer, &i, paths)))
			return (NULL);
		nbr--;
		if (nbr != 0)
		{
			while (lexer[i][0] != ';')
				i += 1;
			i += 1;
		}
	}
	return (parser);
}
