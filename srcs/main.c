/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/04/07 15:15:43 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int     global;

void		display_put(t_redi *redi)
{
    //printf("put = %s, type = %d\n", redi->put, redi->type);
    if (redi->next != NULL)
        display_put(redi->next);
}

void        display_parser(t_pipes *parser)
{
    static int  nbr = 1;
    int         i;
    int         n;
    i = 0;
    n = 0;
    //printf("command\n");
    while (parser->command[i] != NULL)
    {
        printf("command %d : ", nbr++);
        while (parser->command[i] != NULL)
            printf("[%s] ", parser->command[i++]);
        n = 0;
        printf("\n");
    }
    if (parser->redi != NULL)
        display_put(parser->redi);
    if (parser->next != NULL)
        display_parser(parser->next);
}

void        display_total(t_parser *parser)
{
    static int  i = 1;
//      printf("((%p))\n”,parser);
    //printf("\n\nligne command:%d {%p}\n”, i++, parser");
    if ( parser->pipe != NULL)
    display_parser(parser->pipe);
    if (parser->next != NULL)
    {
//      printf("%p\n”,parser->next);
        display_total(parser->next);
    }
}

char    **init_path(char **path)
{
    int     i;
    char    **tab;
    char    *dest;
    i = 0;
    while (path[i] != NULL)
    {
        if (ft_strncmp(path[i], "PATH=", 5) == 0)
            tab = ft_split(path[i], ':'); /// a free
        i++;
    }
    return (tab);
}

static void		int_handler(int signum) // ctrl '\'
{
	ft_putstr_fd("\n[minishell]$", 2);
	global++;
}

static void		quit_handler(int signum) // ctrl '\'
{
    exit(0);
}

int     main(int    argc, char **argv, char **path)
{
	char		*line;
	int 		i;
	t_path		paths;
	t_parser	*parser;
	char		**token;
	char		**exec_path;
	int			status;

	global = 0;
	paths.exec_path = init_path(path);
	paths.path = path;
	line = NULL;
	global = 1;
	ft_putstr_fd("[minishell]$", 2);
	while (global > 0)
	{
		global = 1;
    	signal(SIGINT, int_handler);
		signal(SIGQUIT, quit_handler);
		//printf("%d\n", global);
		if (global != 2)
		{	
			if (get_next_line(0, &line) == 2)
				exit(EXIT_SUCCESS);
			printf("DEBUT TOKEN\n");
			if (line != NULL)
				token = tokenization(line, path);
			printf("FIN TOKEN\n");
			if (token != NULL && token[0] != NULL)
			{
				parser = init_parser(token, &i);
				ft_shell(parser, paths);
				free_parser(parser);
			}
			ft_putstr_fd("[minishell]$", 2);
			free_token(token);
			free(line);
		}
	}
	return (1);
}
