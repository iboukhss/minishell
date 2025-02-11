/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:16 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 15:54:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"

/*
 * Finds the proper shell builtin.
 */
int	exec_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		return (builtin_env(cmd, shell));
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		return (builtin_unset(cmd, shell));
	}
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		return (builtin_export(cmd, shell));
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		return (builtin_exit(cmd, shell));
	}
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		return (builtin_echo(cmd));
	}
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		return (builtin_pwd(cmd));
	}
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		return (builtin_cd(cmd, shell));
	}
	return (MS_XFAILURE);
}
