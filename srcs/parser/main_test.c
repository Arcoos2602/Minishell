/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:57:58 by gbabeau           #+#    #+#             */
/*   Updated: 2021/06/08 16:32:21 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void		display_redi(t_redi *redi)
{
	printf("type = %d, name: %s\n", redi->type, redi->put);
	if ( redi->next != NULL)
		display_redi(redi->next);
}
void		display_parser(t_pipes *parser)
{
	static int	nbr = 1;
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (parser->command[i] != NULL)
	{
		printf("command %d : ", nbr++);
		while (parser->command[i] != NULL)
			printf("<%s> ", parser->command[i++]);
		n = 0;
		printf("\n");
	}
	printf("%p\n", parser->command[i]);
	i = -1;
	n = 0;
		if ( parser->redi != NULL)
			display_redi(parser->redi);
	if (parser->next != NULL)
		display_parser(parser->next);
}

void		display_total(t_parser *parser)
{
	static int	i = 1;

	printf("\n\nligne command:%d\n", i++);
	display_parser(parser->pipe);
	if (parser->next != NULL)
		display_total(parser->next);
}

/*int			main(int a, char **argc)
{
	int			i;
	t_parser	*parser;

	argc[a - 1] = NULL;
	parser = init_parser(&argc[1], &i);
	display_total(parser);
	free(parser);
	return (0);
}*/
