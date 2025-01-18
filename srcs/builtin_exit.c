/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:37:48 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/07 12:54:26 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

// TODO(ismail): Handle more error codes.
int	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strv_length(cmd->args);
	if (argc == 1)
	{
		free_cmd_list(cmd);
		//DHE: As per my understanding, we need to free the shell struct here but we need to adjust the return value accordingly
		//free_shell(shell);
		exit(shell->exit_status);
	}
	else if (argc == 2)
	{
		free_cmd_list(cmd);
		//DHE: As per my understanding, we need to free the shell struct here but we need to adjust the return value accordingly
		//free_shell(shell);
		exit(atoi(cmd->args[1]));
	}
	else
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (MS_XBADUSAGE);
	}
}
