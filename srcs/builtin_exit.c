/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:37:48 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/14 17:10:35 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>

void	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	status;

	argc = ft_strlenv(cmd->args);
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
