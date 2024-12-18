/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:39:56 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/19 13:44:27 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// Add function prototypes here
void	exec_command(t_command *cmd, t_shell *shell);
void	exec_builtin(t_command *cmd, t_shell *shell);

void	exit_shell(int status, t_shell *shell);
int		setup_redirections(t_command *cmd);

char	*get_env(const char *key, t_shell *shell);
void	unset_env(const char *key, t_shell *shell);
void	set_env(const char *expr, t_shell *shell);

// Builtins
void	builtin_env(t_command *cmd, t_shell *shell);
void	builtin_unset(t_command *cmd, t_shell *shell);
void	builtin_export(t_command *cmd, t_shell *shell);
void	builtin_exit(t_command *cmd, t_shell *shell);
void	builtin_echo(t_command *cmd, t_shell *shell);
void	builtin_pwd(t_command *cmd, t_shell *shell);
void	builtin_cd(t_command *cmd, t_shell *shell);

#endif
