/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:42:18 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/05 20:00:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include "libft.h"
#include <string.h>

int	builtin_echo(t_command *cmd)
{
	bool	newline;
	int		argc;
	int		i;

	argc = ft_strv_length(cmd->args);
	newline = 1;
	i = 1;
	if (argc >= 2 && strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (i < argc)
	{
		ft_printf("%s", cmd->args[i]);
		if (i + 1 < argc)
		{
			ft_printf(" ");
		}
		i++;
	}
	if (newline)
	{
		ft_printf("\n");
	}
	return (MS_XSUCCESS);
}
