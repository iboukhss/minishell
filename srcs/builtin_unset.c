/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:27 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:04:29 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdio.h>

int	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strv_length(cmd->args);
	if (argc != 2)
	{
		log_error("unset: too many arguments");
		return (MS_XBADUSAGE);
	}
	unset_env(cmd->args[1], shell);
	return (MS_XSUCCESS);
}
