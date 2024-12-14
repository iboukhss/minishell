/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:37:16 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/14 17:16:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>
#include <string.h>

void	builtin_export(t_command *cmd, t_shell *shell)
{
	char	*key;
	int		key_len;
	char	**envp;
	int		envp_len;
	char	**new_env;
	char	*beg, *end;
	int		i;

	beg = cmd->args[1];
	end = ft_strchrnul(beg, '=');
	key_len = end - beg;
	key = strndup(beg, key_len);
	envp = shell->envs;
	envp_len = ft_strlenv(envp);
	// Variable doesn't exist, allocate new slot
	if (get_env(key, shell) == NULL)
	{
		new_env = ft_xmalloc((envp_len + 2) * sizeof(*new_env));
		i = 0;
		while (*envp != NULL)
		{
			new_env[i++] = *envp;
			envp++;
		}
		new_env[i++] = ft_xstrdup(beg);
	}
	// Variable already exists, overwrite it
	else
	{
		new_env = ft_xmalloc((envp_len + 1) * sizeof(*new_env));
		i = 0;
		while (*envp != NULL)
		{
			// TOFIX(ismail): Doesn't work 100% of the time
			if (ft_strncmp(*envp, key, key_len) == 0)
			{
				free(*envp);
				new_env[i++] = ft_xstrdup(beg);
			}
			else
			{
				new_env[i++] = *envp;
			}
			envp++;
		}
	}
	new_env[i] = NULL;
	free(key);
	free(shell->envs);
	shell->envs = new_env;
	shell->exit_status = 0;
}
