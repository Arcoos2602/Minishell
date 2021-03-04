#include "../includes/minishell.h"
#include "../libft/include/libft.h"

void		signal_handler(int signum)
{
	printf("Caught signal %d\n", signum);
}

int		main(int argc, char **argv)
{
	int		signum = 10;
	int		pid;
	char	buf[486153];

	pid = read(1, buf, 4854);
	if (pid == 0)
		exit(0);
	return (0);
}

/// SIGINT ctrl c
/// SIGQUIT ctrl \
/// EOF ctrl d