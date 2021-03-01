#include "../includes/minishell.h"
#include "../libft/include/libft.h"

int	main(int argc, char **argv)
{
	pid_t		pid;
	int		pipe_fd[2];
	int		status;
	char	*tab[3];
	char	*tab2[3];

	tab[2] = "Makefile\0";
	tab[0] = "/bin/cat";
	tab[1] = "-n\0";
	tab2[2] = "Makefile\0";
	tab2[0] = "/bin/ls";
	tab2[1] = "-n\0";
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[1], 1);
		execve(tab[0], &tab[0],  (char *const*) NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		printf("tets\n");
		execve(tab2[0], &tab2[0],  (char *const*) NULL);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	while (1) {}
	return (0);
}
