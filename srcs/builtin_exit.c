/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:37:48 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/21 22:25:06 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

// TODO(ismail): atoi can fail, needs improvement.
void	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	status;

	argc = ft_strv_length(cmd->args);
	if (argc == 1)
	{
		status = shell->exit_status;
		exit_shell(status, shell);
	}
	else if (argc == 2)
	{
		status = atoi(cmd->args[1]);
		exit_shell(status, shell);
	}
	else
	{
		fprintf(stderr, "exit: too many arguments\n");
		shell->exit_status = 1;
	}
}
