/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/24 00:34:44 by user42           ###   ########.fr       */
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
	rl_on_new_line();
	g_global = 130;
}

static void	quit_handler(int signum)// ctrl '\'
{
	printf("signum=%d\n", signum);
	g_global = 131;
	//exit(0);
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
			path[i++] = ft_strdup(env[n]);
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
	paths.exit_status = 0;
	paths.in_fd = dup(0);
	paths.out_fd = dup(1);
	line = NULL;
	while (1)
	{
		paths.exec_path = ft_split(ft_getenv(paths.path,"PATH"), ':');
		signal(SIGINT, int_handler);
		signal(SIGQUIT, quit_handler);
		line = readline("[minishell]$");
//		printf("valeur retour = %d\n", paths.exit_status);
		add_history(line);
		if (line == NULL)
				exit(0);	
			if (line != NULL)
			{
				token = tokenization(line, paths.path);
				free(line);
			}
			if (token != NULL && token[0] != NULL)
			{
				parser = init_parser(token, &i);
				free_token(token);
				ft_shell(parser, &paths);
				free_parser(parser);
			}
			else
				g_global = 0;
		free_paths(&paths);
//		printf("valeur retour = %d\n",  paths.exit_status);
		g_global = 0;
	}
	rl_clear_history();
	return (1);
}
