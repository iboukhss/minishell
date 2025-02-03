/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:28 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/03 17:08:07 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

// NOTE(ismail): Will fail if the current working directory is somehow longer
// than PATH_MAX.
int	builtin_pwd(t_command *cmd)
{
	int		argc;
	char	cwd[PATH_MAX];

	argc = ft_strv_length(cmd->args);
	if (argc != 1)
	{
		log_error("pwd: too many arguments\n");
		return (MS_XBADUSAGE);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd: getcwd");
		return (MS_XFAILURE);
	}
	puts(cwd);
	return (MS_XSUCCESS);
}
