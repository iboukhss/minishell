/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:39 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 19:59:59 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	search_in_path(char **cmd_path, const char *cmd_name,
				const char *path_var)
{
	char		*dir_name;
	const char	*beg;
	const char	*end;

	beg = path_var;
	end = beg;
	while (*end)
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
	return (MS_XNOTFOUND);
}

int	find_command(char **cmd_path, const char *cmd_name, t_shell *shell)
{
	const char	*path_var;

	if (access(cmd_name, X_OK) == 0)
	{
		*cmd_path = ft_xstrdup(cmd_name);
		return (MS_XSUCCESS);
	}
	path_var = get_env("PATH", shell);
	if (!path_var)
	{
		log_error("PATH variable not set");
		return (MS_XNOTFOUND);
	}
	if (search_in_path(cmd_path, cmd_name, path_var) != 0)
	{
		log_error("minishell: command not found");
		return (MS_XNOTFOUND);
	}
	return (MS_XSUCCESS);
}

/*
 * (void)0 is a no-op for norminette
 */
int	wait_for_all_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		(void)0;
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
