#include "../includes/minishell.h"
#include "../libft/include/libft.h"

int		ft_ballec(int *i)
{
	printf("%p\n", i);
}

int		main(int argc, char **argv, char **path)
{
	int		*i;
	pid_t	pid;

	i = malloc(sizeof(int));
	*i = 0;
	pid = fork();
	if (pid == 0)
	{
		*i = 1;
	}
	else
	usleep(1000);
	printf("%d %p\n", *i, i);
	return (0);
}
