/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:19:28 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 15:51:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
 * Entrypoint function, checks whether the input is a pipeline or a simple
 * and branches accordingly.
 */
void	exec_command(t_command *cmd, t_shell *shell)
{
	int	err;

	err = redirect_io(cmd, shell);
	if (err)
	{
		restore_io(cmd, shell);
		shell->exit_status = err;
		return ;
	}
	if (cmd->next)
	{
		shell->exit_status = exec_pipeline(cmd, shell);
	}
	else
	{
		shell->exit_status = exec_simple_command(cmd, shell);
	}
	restore_io(cmd, shell);
}
