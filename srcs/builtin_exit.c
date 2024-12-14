/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:37:48 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/14 12:42:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <stdlib.h>

static int	strlenv(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	status;

	argc = strlenv(cmd->args);
	if (argc < 2)
	{
		status = shell->exit_status;
	}
	else
	{
		status = atoi(cmd->args[1]);
	}
	exit_shell(status, shell);
}
