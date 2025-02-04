/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:54:29 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:03:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdio.h>

int	builtin_env(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	**envp;

	argc = ft_strv_length(cmd->args);
	if (argc != 1)
	{
		log_error("env: too many arguments");
		return (MS_XBADUSAGE);
	}
	envp = shell->envs;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (MS_XSUCCESS);
}
