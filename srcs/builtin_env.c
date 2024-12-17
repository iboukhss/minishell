/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:54:29 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/17 08:12:35 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <stdio.h>

void	builtin_env(t_command *cmd, t_shell *shell)
{
	char	**envp;

	(void)cmd;
	envp = shell->envs;
	while (*envp != NULL)
	{
		puts(*envp);
		envp++;
	}
}
