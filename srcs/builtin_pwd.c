/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:28 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/18 14:29:13 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	builtin_pwd(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	cwd[PATH_MAX];

	argc = ft_strlenv(cmd->args);
	if (argc == 1)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			perror("getcwd");
			exit(EXIT_FAILURE);
		}
		puts(cwd);
		shell->exit_status = 1;
	}
	else
	{
		shell->exit_status = 1;
	}
}
