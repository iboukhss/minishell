/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:08:38 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/01 12:24:01 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "sig.h"

#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	redirect_io(t_command *cmd, t_shell *shell)
{
	int		fd;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (cmd->heredoc)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			setup_heredoc_signal_handlers();
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
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			close(pipefd[0]);
			write(STDOUT_FILENO, "\n", 1);
			tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
			return (128 + WTERMSIG(status));
		}
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
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
int	restore_io(t_command *cmd, t_shell *shell)
{
	if (cmd->heredoc || cmd->infile)
	{
		if (dup2(shell->stdin, STDIN_FILENO) == -1)
		{
			perror("dup2: failed to restore stdin");
			return (-1);
		}
	}
	if (cmd->outfile)
	{
		if (dup2(shell->stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2: failed to restore stdout");
			return (-1);
		}
	}
	return (0);
}
