/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/19 12:06:12 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
void		display_parser(t_pipe *parser)
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
			printf("[%s] ", parser->command[i++]);
		n = 0;
		printf("\n");
	}
	nbr = 1;
	//printf("%p\n", parser->command[i]);
	i = -1;
	n = 0;
	while (parser->input[++i] != NULL)
	{
		printf("input %d : ", i + 1);
		while (parser->input[i][n] != NULL)
			printf("[%s] ", parser->input[i][n++]);
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
				printf("[%s]", parser->output_s[i][n++]);
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
				printf("[%s]", parser->output_d[i][n++]);
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

int		main(int	argc, char **argv, char **path)
{
	t_main	vars;
	char		*line;
	(void)argc;
	(void)argv;
	int 		i;
	t_parser	*parser;
	char **toker;

	ft_putstr_fd("$ ", 1);
	if ((!init_all(&vars)))
		return (-1);
	while (1) // boucle principale
	{
		get_next_line(1, &line);
		toker = token(line);
		i = 0;
		while ( toker != NULL && toker[i] != NULL)
			printf("{%s} ", toker[i++]);
		printf("\n");
		i = 0;
//		toker[0] = "<\0";
//		toker[1] = "|\0";
//		toker[2] = NULL;
		parser = init_parser(toker, &i);
		if (parser != NULL)
			display_total(parser);
		free(vars.line);
	}
	return (1);
}
