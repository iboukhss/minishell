/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:24 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/21 22:25:03 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <stdlib.h>
#include <string.h>

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
	char	**new_envp;
	int		envp_len;
	int		key_len;
	int		i;

	if (get_env(key, shell) == NULL)
	{
		return ;
	}
	envp = shell->envs;
	envp_len = ft_strv_length(envp);
	new_envp = ft_xmalloc(envp_len * sizeof(*new_envp));
	key_len = ft_strlen(key);
	i = 0;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '=')
		{
			free(*envp);
		}
		else
		{
			new_envp[i++] = *envp;
		}
		envp++;
	}
	new_envp[i] = NULL;
	free(shell->envs);
	shell->envs = new_envp;
}

void	set_env(const char *expr, t_shell *shell)
{
	char		**envp;
	char		**new_envp;
	char		*key;
	int			envp_len;
	const char	*beg, *end;
	int			i;

	beg = expr;
	end = ft_strchrnul(beg, '=');
	key = strndup(beg, end - beg);
	envp = shell->envs;
	envp_len = ft_strv_length(envp);
	if (get_env(key, shell) == NULL)
	{
		new_envp = ft_xmalloc((envp_len + 2) * sizeof(*new_envp));
		i = 0;
		while (*envp != NULL)
		{
			new_envp[i++] = *envp;
			envp++;
		}
		new_envp[i++] = ft_xstrdup(expr);
	}
	else
	{
		new_envp = ft_xmalloc((envp_len + 1) * sizeof(*new_envp));
		i = 0;
		while (*envp != NULL)
		{
			if (ft_strncmp(*envp, key, end - beg) == 0 && (*envp)[end - beg] == '=')
			{
				free(*envp);
				new_envp[i++] = ft_xstrdup(expr);
			}
			else
			{
				new_envp[i++] = *envp;
			}
			envp++;
		}
	}
	new_envp[i] = NULL;
	free(key);
	free(shell->envs);
	shell->envs = new_envp;
}
