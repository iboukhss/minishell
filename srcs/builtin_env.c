/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:54:29 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/13 16:08:50 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <stdio.h>

void	builtin_env(t_command *cmd, t_shell *shell)
{
	int	i;

	(void)cmd;
	i = 0;
	while (shell->envs[i] != NULL)
	{
		printf("%s\n", shell->envs[i]);
		i++;
	}
}
