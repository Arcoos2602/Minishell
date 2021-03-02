#include "../includes/minishell.h"
#include "../libft/include/libft.h"

int *ft_pipe_2(int *i, int pipe_fd[2])
{
	pid_t		pid;
	int		*pipe_fd_2;
	int		status;

	char	*tab2[3];

	pipe_fd_2 = malloc(sizeof(int) *2);
	tab2[0] = "/bin/cat\0";
	tab2[1] = "-n\0";
	tab2[2] = NULL;
	
	if (*i != 0)
		if (pipe(pipe_fd_2) == -1)
			return (NULL);
	pid = fork();
	if (pid == 0)
	{
			if (pipe_fd[0] != -1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
		}
		if (*i != 0)
			dup2(pipe_fd_2[1], 1);
		execve(tab2[0], &tab2[0],  (char *const*) NULL);
	}

	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(-1, &status, 0);
		waitpid(-1, &status, 0);
	}			
	--*i;
	return (pipe_fd_2);
}

int	main(int argc, char **argv)
{
	int		i = 0;
	int *pipe_fd;

	pipe_fd = malloc(sizeof(int) *2);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (i != -1)
		pipe_fd = ft_pipe_2(&i, pipe_fd);
	while (1)
		;
	return (0);
}
