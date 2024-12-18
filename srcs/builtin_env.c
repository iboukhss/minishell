/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:54:29 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/18 18:36:02 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>

void	builtin_env(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	**envp;

	argc = ft_strlenv(cmd->args);
	envp = shell->envs;
	if (argc == 1)
	{
		while (*envp != NULL)
		{
			puts(*envp);
			envp++;
		}
		shell->exit_status = 0;
	}
	else
	{
		shell->exit_status = 1;
	}
}
