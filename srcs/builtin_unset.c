/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:27 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/21 22:25:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>

void	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	argc;

	argc = ft_strv_length(cmd->args);
	if (argc == 2)
	{
		unset_env(cmd->args[1], shell);
		shell->exit_status = 0;
	}
	else
	{
		fprintf(stderr, "unset: too many arguments\n");
		shell->exit_status = 1;
	}
}
