/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:27 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/15 09:00:59 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>

// NOTE(ismail): Assuming there is always at least 1 argument (cmd->args[1]).
// Find a way to check and count arguments more consistently?
// Is it possible to have duplicate variables?
void	builtin_unset(t_command *cmd, t_shell *shell)
{
	char	*key;
	int		key_len;
	char	**envp;
	int		envp_len;
	char	**new_env;
	int		i;

	if (get_env(cmd->args[1], shell) == NULL)
	{
		shell->exit_status = 1;
		return ;
	}
	key = cmd->args[1];
	key_len = ft_strlen(key);
	envp = shell->envs;
	envp_len = ft_strlenv(envp);
	new_env = ft_xmalloc((envp_len + 1) * sizeof(*new_env));
	i = 0;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '=')
		{
			free(*envp);
		}
		else
		{
			new_env[i++] = *envp;
		}
		envp++;
	}
	new_env[i] = NULL;
	free(shell->envs);
	shell->envs = new_env;
	shell->exit_status = 0;
}
