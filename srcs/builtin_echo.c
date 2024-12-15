/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:42:18 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/15 06:52:15 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>

// TODO(ismail): Implement the "-n" option.
void	builtin_echo(t_command *cmd, t_shell *shell)
{
	int	argc;
	int	i;

	argc = ft_strlenv(cmd->args);
	i = 1;
	while (i < argc)
	{
		if (i + 1 == argc)
		{
			(void)printf("%s\n", cmd->args[i]);
		}
		else
		{
			(void)printf("%s ", cmd->args[i]);
		}
		i++;
	}
	shell->exit_status = 0;
}
