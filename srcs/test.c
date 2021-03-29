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
