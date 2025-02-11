/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:24 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 14:26:57 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

char	*get_env(const char *key, t_shell *shell)
{
	char	**envp;
	int		key_len;
	int		i;

	envp = shell->envs;
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (envp[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}

void	unset_env(const char *key, t_shell *shell)
{
	char	**envp;
	int		key_len;
	int		slots_left;
	int		i;

	envp = shell->envs;
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			slots_left = ft_strv_length(&envp[i]);
			free(envp[i]);
			ft_memmove(&envp[i], &envp[i + 1], slots_left * sizeof(*envp));
			break ;
		}
		else
		{
			i++;
		}
	}
}

/*
 * Renamed envp to e because of norm.
 */
void	set_env(const char *key, const char *val, t_shell *shell)
{
	int		i;
	size_t	key_len;
	char	*expr;
	char	**e;
	char	**new_envp;

	i = 0;
	key_len = ft_strlen(key);
	expr = ft_xasprintf("%s=%s", key, val);
	e = shell->envs;
	while (e[i] != NULL)
	{
		if (ft_strncmp(e[i], key, key_len) == 0 && e[i][key_len] == '=')
		{
			free(e[i]);
			e[i] = expr;
			return ;
		}
		i++;
	}
	new_envp = ft_xrealloc(e, (i + 1) * sizeof(*e), (i + 2) * sizeof(*e));
	new_envp[i] = expr;
	new_envp[i + 1] = NULL;
	shell->envs = new_envp;
}
