#include "../includes/minishell.h"
#include "../libft/include/libft.h"

void		signal_handler(int signum)
{
	printf("Caught signal %d\n", signum);
}

int		main(int argc, char **argv, char **path)
{
	chdir("srcs");

}

/// SIGINT ctrl c
/// SIGQUIT ctrl
/// EOF ctrl d