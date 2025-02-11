/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:27 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 20:50:32 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdio.h>

int	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	i;

	argc = ft_strv_length(cmd->args);
	i = 1;
	while (i < argc)
	{
		unset_env(cmd->args[i], shell);
		i++;
	}
	return (MS_XSUCCESS);
}
