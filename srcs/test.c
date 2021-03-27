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
	execve("/bin/ls", &argv[1] , (char *const*) NULL);
	return (0);
}
