/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:08:38 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 20:31:04 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	redirect_input(t_command *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->infile);
		return (MS_XFAILURE);
	}
	ft_xdup2(fd, STDIN_FILENO);
	close(fd);
	return (MS_XSUCCESS);
}

static int	redirect_output(t_command *cmd)
{
	int	fd;

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
	ft_xdup2(fd, STDOUT_FILENO);
	close(fd);
	return (MS_XSUCCESS);
}

int	redirect_io(t_command *cmd, t_shell *shell)
{
	int	err;

	if (cmd->heredoc)
	{
		err = handle_heredoc(cmd, shell);
		if (err)
			return (err);
	}
	else if (cmd->infile)
	{
		err = redirect_input(cmd);
		if (err)
			return (err);
	}
	if (cmd->outfile)
	{
		err = redirect_output(cmd);
		if (err)
			return (err);
	}
	return (MS_XSUCCESS);
}

// Cleanup function
int	restore_io(t_command *cmd, t_shell *shell)
{
	if (cmd->heredoc || cmd->infile)
	{
		ft_xdup2(shell->stdin, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		ft_xdup2(shell->stdout, STDOUT_FILENO);
	}
	return (0);
}
