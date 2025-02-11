/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:56 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 16:00:34 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Executes an external binary and returns the proper exit status.
 */
int	exec_external(t_command *cmd, t_shell *shell)
{
	char	*bin_path;
	int		err;

	err = find_command(&bin_path, cmd->args[0], shell);
	if (err)
	{
		return (err);
	}
	execve(bin_path, cmd->args, shell->envs);
	perror(cmd->args[0]);
	free(bin_path);
	return (MS_XFAILURE);
}
