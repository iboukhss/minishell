/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:28 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/17 13:50:13 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdio.h>

void	builtin_pwd(t_command *cmd, t_shell *shell)
{
	int		argc;
	char	*cwd;

	argc = ft_strlenv(cmd->args);
	if (argc == 1)
	{
		cwd = get_env("PWD", shell);
		if (cwd == NULL)
		{
			// Find something else
		}
		else
		{
			puts(cwd);
		}
	}
}
