/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:08:38 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/14 14:39:54 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// NOTE(ismail): The file descriptor table is copied on fork() but remains
// separate between processes, that means, modifications to the file
// descriptors of the child process won't propagate back to the parent process.
int	setup_redirections(t_command *cmd)
{
	int	fd;
	int	oflags;

	if (cmd->outfile)
	{
		oflags = O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC);
		fd = open(cmd->outfile, oflags, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}
