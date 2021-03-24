/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/24 15:13:56 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int			global;

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

void    int_handler(int signum) // ctrl   c
{
	exit(0);
}

void    quit_handler(int signum) // ctrl
{

}

int     main(int    argc, char **argv, char **path)
{
	char		*line;
	int 		i;
	t_path		paths;
	t_parser	*parser;
	char		**token;
	char		**exec_path;
	int			*pipe_fd;
	int			status;
	struct  rusage rusage;

	pipe_fd = malloc(sizeof(int) * 2);
	paths.exec_path = init_path(path);
	paths.path = path;
	global = 1;
	while (global > 0)
	{
		global = 1;
		signal(SIGQUIT, quit_handler);
		ft_putstr_fd("[minishell]$", 2);
		get_next_line(0, &line);
		signal(SIGINT, int_handler);
		if (global == 2)
			line = NULL;
		token = tokenization(line, path);
		if (token != NULL && token[0] != NULL)
		{
			parser = init_parser(token, &i);
			pipe_fd = ft_shell(parser, pipe_fd, paths);
			//free_parser(parser);
		}
		//free_token(token);
		free(line);
	}
	free(pipe_fd);
	return (1);
}
