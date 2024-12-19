/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:44:17 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/19 17:01:09 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	builtin_cd(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	*new_cwd;

	argc = ft_strlenv(cmd->args);
	if (argc == 1)
	{
		new_cwd = get_env("HOME", shell);
		if (new_cwd == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			shell->exit_status = 1;
			// Need to be more careful about this stuff here
			return ;
		}
		if (chdir(new_cwd) < 0)
		{
			perror("cd: chdir");
			shell->exit_status = 1;
		}
	}
	else if (argc == 2)
	{
		new_cwd = cmd->args[1];
		if (chdir(new_cwd) < 0)
		{
			perror("cd: chdir");
			shell->exit_status = 1;
		}
	}
	else
	{
		fprintf(stderr, "cd: too many arguments\n");
		shell->exit_status = 1;
	}
}
