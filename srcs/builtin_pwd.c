/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:28 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/19 14:44:30 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// NOTE(ismail): Will fail if the current working directory is somehow longer
// than PATH_MAX.
void	builtin_pwd(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	cwd[PATH_MAX];

	argc = ft_strlenv(cmd->args);
	if (argc == 1)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			perror("pwd: getcwd");
			shell->exit_status = 1;
			return ;
		}
		puts(cwd);
		shell->exit_status = 0;
	}
	else
	{
		fprintf(stderr, "pwd: too many arguments\n");
		shell->exit_status = 1;
	}
}
