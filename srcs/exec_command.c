/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:53 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/29 18:33:17 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// DESC: Checks if a command is an absolute path and if so, executes it.
// Otherwise, we look for the executable within the PATH environment variable.
void	exec_command(char *command, char **argv, char **envp)
{
	char	*path;
	char	full_path[PATH_MAX];

	if (access(command, X_OK) == 0)
	{
		execve(command, argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	path = getenv("PATH");
	char *beg = path;
	while (1)
	{
		char *end = ft_strchrnul(beg, ':');
		if (end - beg == 0)
		{
			fprintf(stderr, "%s: command not found\n", command);
			exit(EXIT_FAILURE);
		}
		// Assuming no overflow on full_path (tofix)
		ft_memcpy(full_path, beg, end - beg);
		full_path[end - beg] = '/';
		ft_memcpy(full_path + (end - beg) + 1, command, ft_strlen(command) + 1);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, argv, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		beg = end + 1;
	}
}

/*
int	main(int argc, char **argv, char **envp)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	exec_command(argv[1], &argv[1], envp);
	return (0);
}
*/
