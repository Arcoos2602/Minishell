/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:59:22 by tcordonn          #+#    #+#             */
/*   Updated: 2021/01/29 14:53:09 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int	argc, char **argv, char **envv)
{
	int fd;
	char *a;
	DIR *d;
	struct dirent *dir;
	char *const tab[] = {"/bin/grep", "", "", NULL};
//	fd = open("/bin", O_DIRECTORY, O_APPEND);
	d = opendir("/bin");
	while((dir = readdir(d)) != NULL)
		printf("%s\n", dir->d_name);
	execve(tab[0], tab, NULL);
	//printf("%s\n", envv[11]);
}