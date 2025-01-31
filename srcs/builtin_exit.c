/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:37:48 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:43:16 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "parse.h"

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// TODO(ismail): Handle more error codes.
int	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	last_exit_status;

	argc = ft_strv_length(cmd->args);
	if (argc == 1)
	{
		last_exit_status = shell->exit_status;
		free_cmd_list(cmd);
		clear_history();
		free_shell(shell);
		exit(last_exit_status);
	}
	else if (argc == 2)
	{
		last_exit_status = atoi(cmd->args[1]);
		free_cmd_list(cmd);
		clear_history();
		free_shell(shell);
		exit(last_exit_status);
	}
	else
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (MS_XBADUSAGE);
	}
}
