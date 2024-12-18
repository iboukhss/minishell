/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:27 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/18 13:17:02 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strlenv(cmd->args);
	if (argc == 2)
	{
		if (unset_env(cmd->args[1], shell) == 0)
		{
			shell->exit_status = 0;
		}
		else
		{
			shell->exit_status = 1;
		}
	}
	else
	{
		shell->exit_status = 1;
	}
}
