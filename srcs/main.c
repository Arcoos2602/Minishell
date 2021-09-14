/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/09 19:00:12 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	g_global;

void	display_put(t_redi *redi)
{
	printf("put = %s, type = %d\n", redi->put, redi->type);
	if (redi->next != NULL)
		display_put(redi->next);
}

void	display_parser(t_pipes *parser)
{
	static int	nbr = 1;
	int			i;

	i = 0;
		//printf("command\n");
	while (parser->command[i] != NULL)
	{
		printf("command %d : ", nbr++);
		while (parser->command[i] != NULL)
			printf("[%s] ", parser->command[i++]);
		printf("\n");
	}
	if (parser->redi != NULL)
		display_put(parser->redi);
	if (parser->next != NULL)
		display_parser(parser->next);
}

void	display_total(t_parser *parser)
{
	static int	i = 1;
//      printf("((%p))\n”,parser);
	//printf("\n\nligne command:%d {%p}\n”, i++, parser");
	if (parser->pipe != NULL)
		display_parser(parser->pipe);
	if (parser->next != NULL)
	{
      printf("%d\n",i);
		display_total(parser->next);
	}
}

char	**init_path(char **path)
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
	return (tab);
}

static void	int_handler(int signum)// ctrl '\'
{
	printf("signum=%d\n", signum);
	ft_putstr_fd("\n[minishell]$", 2);
	g_global++;
}

static void	quit_handler(int signum)// ctrl '\'
{
	printf("signum=%d\n", signum);
	exit(0);
}

void	free_paths(t_path *path)
{
	int	i;

	i = 0;
	if(path != NULL && path->exec_path != NULL)
	{
	while (path->exec_path[i] != NULL)
		free(path->exec_path[i++]);
	free(path->exec_path);
	}
}

static char	**env_malloc(char **path, char **env)
{
	int	n;
	int	i;

	n = -1;
	while (env[++n] != NULL)
	;
	path = malloc((n + 1) * sizeof(char *));
	i = 0;
	n = -1;
	while (env[++n] != NULL)
	{
			printf("a\n");
			path[i++] = ft_strdup(env[n]);
	}
	path[i]= NULL;
	return (path);
}

int	main(int argc, char **argv, char **path)
{
	char		*line;
	t_path		paths;
	t_parser	*parser;
	char		**token;
	int			i;
//	char		**exec_path;
//	int			status;

	i = 0;
	g_global = 0;
	printf("argc = %d et argv = %s\n", argc, argv[0]);
	path = env_malloc(paths.path, path);
	paths.path = path;
	line = NULL;
	g_global = 1;
	while (g_global >= 0)
	{
		paths.exec_path = ft_split(ft_getenv(paths.path,"PATH"), ':');
		g_global = 1;
		signal(SIGINT, int_handler);
		signal(SIGQUIT, quit_handler);
		if (g_global != 2)
		{	
			line = readline("[minishell]$");
			add_history(line);
			if (line == NULL)
				exit(0);
			if (line != NULL)
			{
				token = tokenization(line);
				free(line);
			}
			if (token != NULL && token[0] != NULL)
			{
				parser = init_parser(token, &i);
				free_token(token);
				ft_shell(parser, &paths);
				free_parser(parser);
			}
			free_paths(&paths);
			printf("%d\n", g_global);
		}
	}
	rl_clear_history();
	return (1);
}
