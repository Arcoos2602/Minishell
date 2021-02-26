/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/26 13:24:03 by tcordonn         ###   ########.fr       */
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
//	printf("%p\n", parser->command[i]);
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
//		printf("u\n");
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
//		printf("u\n");
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
//		printf("uu\n");
	if (parser->next != NULL)
		display_parser(parser->next);
}

void		display_total(t_parser *parser)
{
	static int	i = 1;

//		printf("((%p))\n",parser);
	printf("\n\nligne command:%d\n", i++);
	display_parser(parser->pipe);
	if (parser->next != NULL)
	{
//		printf("%p\n",parser->next);
		display_total(parser->next);
	}
}

char	**init_path(t_pipe *parser, char **path)
{
	int		i;
	char	**tab;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strncmp(path[i], "PATH=", 5) == 0)
			tab = ft_split(path[i], ':');
		i++;
	}
}

int		main(int	argc, char **argv, char **path)
{
	t_main		vars;
	char		*line;
	int 		i;
	t_parser	*parser;
	char		**token;
	char		**exec_path;

	(void)argc;
	(void)argv;
	ft_putstr_fd("$ ", 1);
	if ((!init_all(&vars)))
		return (-1);
	exec_path = init_path(parser->pipe, path);
	while (1) // boucle principale
	{
		get_next_line(1, &line);
		token = tokenization(line);
		/*while ( token != NULL && token[i] != NULL)
			printf("{%s} ", token[i++]);
		printf("\n");*/
		parser = init_parser(token, &i);
		//check_builtins(parser);
		/*if (parser != NULL)
			display_total(parser);*/
		free(vars.line);
	}
	return (1);
}
