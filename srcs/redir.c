/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:08:38 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/30 17:22:08 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// NOTE(ismail): Error handling is not perfect but it should be fine.
/*
Description: Backs up the standard input and/or standard output file descriptors 
if the command involves a heredoc, input redirection, or output redirection.
Saves the current file descriptors to the provided pointers.
*/
int	backup_io(t_command *cmd, int *saved_stdin, int *saved_stdout)
{
	if (cmd->heredoc || cmd->infile)
	{
		*saved_stdin = dup(STDIN_FILENO);
		if (*saved_stdin == -1)
		{
			perror("dup: failed to backup stdin");
			return (-1);
		}
	}
	if (cmd->outfile)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdout == -1)
		{
			perror("dup: failed to backup stdout");
			return (-1);
		}
	}
	return (0);
}

int	redirect_io(t_command *cmd)
{
	int		fd;
	int		pipefd[2];
	pid_t	pid;

	if (cmd->heredoc)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			while (1)
			{
				char *line = readline("> ");
				if (line == NULL || strcmp(line, cmd->heredoc) == 0)
				{
					free(line);
					break ;
				}
				dprintf(pipefd[1], "%s\n", line);
				free(line);
			}
			close(pipefd[1]);
			exit(MS_XSUCCESS);
		}
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			return (MS_XFAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append_mode)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd == -1)
		{
			perror(cmd->outfile);
			return (MS_XFAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

// Cleanup function
int	restore_io(t_command *cmd, int saved_stdin, int saved_stdout)
{
	if (cmd->heredoc || cmd->infile)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2: failed to restore stdin");
			return (-1);
		}
		close(saved_stdin);
	}
	if (cmd->outfile)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2: failed to restore stdout");
			return (-1);
		}
		close(saved_stdout);
	}
	return (0);
}
