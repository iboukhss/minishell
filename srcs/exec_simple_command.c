/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:00 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 16:02:32 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

/*
 * Executes a simple command, which can be of two forms: a shell builtin
 * function or an external binary.
 */
int	exec_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	if (cmd->is_builtin)
	{
		return (exec_builtin(cmd, shell));
	}
	else
	{
		pid = ft_xfork();
		if (pid == 0)
		{
			exit(exec_external(cmd, shell));
		}
		return (wait_for_all_children());
	}
}
