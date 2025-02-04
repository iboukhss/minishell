/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:37:16 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 18:08:32 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

int	builtin_export(t_command *cmd, t_shell *shell)
{
	int		i;
	int		argc;
	char	*key;
	char	*val;
	char	*end;

	argc = ft_strv_length(cmd->args);
	if (argc < 2)
	{
		log_error("export: not enough arguments");
		return (MS_XBADUSAGE);
	}
	i = 1;
	while (i < argc)
	{
		end = ft_strchr(cmd->args[i], '=');
		if (end)
		{
			key = ft_xstrndup(cmd->args[i], end - cmd->args[i]);
			val = ft_xstrdup(end + 1);
			set_env(key, val, shell);
			free(key);
			free(val);
		}
		i++;
	}
	return (MS_XSUCCESS);
}
