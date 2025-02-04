/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:44:17 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 20:33:29 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

int	builtin_cd(t_command *cmd, t_shell *shell)
{
	int			argc;
	const char	*target;
	char		old_cwd[PATH_MAX];
	char		new_cwd[PATH_MAX];

	argc = ft_strv_length(cmd->args);
	if (argc == 1)
	{
		target = get_env("HOME", shell);
		if (target == NULL)
		{
			log_error("cd: HOME not set");
			return (MS_XFAILURE);
		}
	}
	else if (argc == 2)
	{
		target = cmd->args[1];
	}
	else
	{
		log_error("cd: too many arguments");
		return (MS_XBADUSAGE);
	}
	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("cd: getcwd");
		return (MS_XFAILURE);
	}
	if (chdir(target) == -1)
	{
		perror("cd: chdir");
		return (MS_XFAILURE);
	}
	if (getcwd(new_cwd, sizeof(new_cwd)) == NULL)
	{
		perror("cd: getcwd");
		return (MS_XFAILURE);
	}
	set_env("OLDPWD", old_cwd, shell);
	set_env("PWD", new_cwd, shell);
	return (MS_XSUCCESS);
}
