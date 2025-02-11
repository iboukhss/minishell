/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:16:20 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 20:26:49 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "sig.h"

#include "libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	handle_heredoc(t_command *cmd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	ft_xpipe(pipefd);
	pid = ft_xfork();
	if (pid == 0)
	{
		close(pipefd[0]);
		setup_heredoc_signal_handlers();
		while (1)
		{
			char *line = readline("> ");
			if (line == NULL || ft_strcmp(line, cmd->heredoc) == 0)
			{
				free(line);
				break ;
			}
			ft_dprintf(pipefd[1], "%s\n", line);
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
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term);
		return (128 + WTERMSIG(status));
	}
	ft_xdup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (MS_XSUCCESS);
}
