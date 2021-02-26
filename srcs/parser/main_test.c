/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:57:58 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/26 15:26:25 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

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
	while (parser->input[++i] != NULL)
	{
		printf("input %d : ", i + 1);
		while (parser->input[i][n] != NULL)
			printf("<%s> ", parser->input[i][n++]);
		n = 0;
		printf("\n");
	}
	i = -1;
	n = 0;
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_s %d : ", i + 1);
		if (parser->output_s[i] != NULL)
			while (parser->output_s[i][n] != NULL)
				printf("<%s>", parser->output_s[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
	i = -1;
	n = 0;
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_d %d : ", i + 1);
		if (parser->output_d[i] != NULL)
			while (parser->output_d[i][n] != NULL)
				printf("<%s>", parser->output_d[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
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
