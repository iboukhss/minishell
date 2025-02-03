/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:37:16 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/03 17:08:08 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdio.h>

// TODO(ismail): Improve this function to handle multiple variables.
int	builtin_export(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strv_length(cmd->args);
	if (argc != 2)
	{
		log_error("export: too many arguments\n");
		return (MS_XBADUSAGE);
	}
	set_env(cmd->args[1], shell);
	return (MS_XSUCCESS);
}
