/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:39 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 17:09:57 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Find the full command path for a binary.
 * Needs improvement.
 */
int	find_command(char **cmd_path, const char *cmd_name, t_shell *shell)
{
	char	*path_var;
	char	*dir_name;
	char	*beg;
	char	*end;

	if (access(cmd_name, X_OK) == 0)
	{
		*cmd_path = ft_xstrdup(cmd_name);
		return (MS_XSUCCESS);
	}
	path_var = get_env("PATH", shell);
	if (path_var == NULL)
	{
		log_error("PATH variable not set");
		return (MS_XNOTFOUND);
	}
	beg = path_var;
	end = beg;
	while (*end != '\0')
	{
		end = ft_strchrnul(beg, ':');
		if (end - beg > 0)
		{
			dir_name = ft_xstrndup(beg, end - beg);
			*cmd_path = ft_xasprintf("%s/%s", dir_name, cmd_name);
			free(dir_name);
			if (access(*cmd_path, X_OK) == 0)
			{
				return (MS_XSUCCESS);
			}
			free(*cmd_path);
		}
		beg = end + 1;
	}
	log_error("minishell: command not found");
	return (MS_XNOTFOUND);
}

int	wait_for_all_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		// wait for all children
	}
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	else
	{
		return (MS_XFAILURE);
	}
}
