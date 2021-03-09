#include "../includes/minishell.h"
#include "../libft/include/libft.h"

int		redirect(char *str, int pipe_fd[2], int type)
{
	int fd;

	if (type == 1)
	{
		fd = open(str, O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0666);
	}
	if (type == 2)
	{
		fd = open(str, O_APPEND | O_CREAT | O_RDWR, 0666);
	}
	write(fd, "d", 1);
	return (fd);
}

int		main(int argc, char **argv, char **path)
{
	int		i;
	int		fd;
	int		pipe_fd[2];

	fd = redirect(argv[1], pipe_fd, ft_atoi(argv[2]));
	close(fd);
	return (0);
}
