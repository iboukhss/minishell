/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:44:17 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:52 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	builtin_cd(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	*new_cwd;

	argc = ft_strv_length(cmd->args);
	if (argc == 1)
	{
		new_cwd = get_env("HOME", shell);
		if (new_cwd == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (MS_XFAILURE);
		}
		if (chdir(new_cwd) == -1)
		{
			perror("cd: chdir");
			return (MS_XFAILURE);
		}
		return (MS_XSUCCESS);
	}
	else if (argc == 2)
	{
		new_cwd = cmd->args[1];
		if (chdir(new_cwd) == -1)
		{
			perror("cd: chdir");
			return (MS_XFAILURE);
		}
		return (MS_XSUCCESS);
	}
	else
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (MS_XBADUSAGE);
	}
}
