/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:08:38 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/30 03:55:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// NOTE(ismail): Error handling is not perfect but it should be fine.

int	backup_io(t_command *cmd, int *saved_stdin, int *saved_stdout)
{
	if (cmd->infile)
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
	int	fd;
	int	flags;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		flags = O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC);
		fd = open(cmd->outfile, flags, 0644);
		if (fd == -1)
		{
			perror(cmd->outfile);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

// Cleanup function
int	restore_io(t_command *cmd, int saved_stdin, int saved_stdout)
{
	if (cmd->infile)
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
