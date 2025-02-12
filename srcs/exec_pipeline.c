/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:31 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 18:17:05 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	exec_from_pipeline(t_command *cmd, t_shell *shell)
{
	redirect_io(cmd, shell);
	if (cmd->is_builtin)
	{
		exit(exec_builtin(cmd, shell));
	}
	else
	{
		exit(exec_external(cmd, shell));
	}
}

static void	handle_child(int prev_fd, int pfd[2], t_command *cmd, t_shell *sh)
{
	if (prev_fd != -1)
	{
		ft_xdup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pfd[0]);
		ft_xdup2(pfd[1], STDOUT_FILENO);
	}
	exec_from_pipeline(cmd, sh);
}

int	exec_pipeline(t_command *cmd, t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next)
			ft_xpipe(pipefd);
		pid = ft_xfork();
		if (pid == 0)
			handle_child(prev_fd, pipefd, cmd, shell);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	return (wait_for_all_children());
}
