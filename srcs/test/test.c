#include "../includes/minishell.h"
#include "../libft/include/libft.h"

int		ft_ballec(int *i)
{
	printf("%p\n", i);
}

int		main(int argc, char **argv, char **path)
{
	int		*i;
	int		fd;
	int 	pipe_fd[2];
	pid_t pid;

	argv[2] = NULL;
	//close(1);
	//close(0);
	execve("/bin/cat", &argv[1] , (char *const*) NULL);

	//close(0);
	/*while(1);
	;*/
	return (0);
}

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

	if (parser->pipe != NULL)
		display_parser(parser->pipe);
	if (parser->next != NULL)
	{
	  printf("%d\n",i);
		display_total(parser->next);
	}
}
