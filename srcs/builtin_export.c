/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:37:16 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/18 16:11:55 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	builtin_export(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strlenv(cmd->args);
	if (argc == 2)
	{
		set_env(cmd->args[1], shell);
		shell->exit_status = 0;
	}
	else
	{
		shell->exit_status = 1;
	}
}
