/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:53 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/02 20:22:46 by iboukhss         ###   ########.fr       */
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
void	exec_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	full_path[PATH_MAX];

	if (access(cmd->args[0], X_OK) == 0)
	{
		execve(cmd->args[0], cmd->args, shell->envs);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH variable not set\n");
		exit(EXIT_FAILURE);
	}
	char *beg = path;
	while (1)
	{
		char *end = ft_strchrnul(beg, ':');
		if (end - beg > 0)
		{
			// Need enough space for '/' and '\0'
			if ((end - beg) + ft_strlen(cmd->args[0]) + 2 > PATH_MAX)
			{
				fprintf(stderr, "Path too long\n");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(full_path, beg, end - beg);
			full_path[end - beg] = '/';
			ft_strcpy(full_path + (end - beg) + 1, cmd->args[0]);
			if (access(full_path, X_OK) == 0)
			{
				execve(full_path, cmd->args, shell->envs);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		if (*end == '\0')
		{
			fprintf(stderr, "%s: command not found\n", cmd->args[0]);
			exit(EXIT_FAILURE);
		}
		beg = end + 1;
	}
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_command	cmd = {argv + 1, 0, NULL, NULL, 0, NULL, NULL};
	t_shell		shell = {envp, 0};

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	exec_command(&cmd, &shell);
	return (0);
}
*/
