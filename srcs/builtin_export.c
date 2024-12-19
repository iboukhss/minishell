/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:37:16 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/19 13:40:42 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>

// TODO(ismail): Improve this function to handle multiple variables.
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
		fprintf(stderr, "export: too many arguments\n");
		shell->exit_status = 1;
	}
}
