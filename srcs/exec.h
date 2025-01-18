/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:39:56 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/07 12:15:42 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// Add function prototypes here
int		find_command(char **cmd_path, const char *cmd_name, t_shell *shell);

void	exec_command(t_command *cmd, t_shell *shell);
int		exec_builtin(t_command *cmd, t_shell *shell);
int		exec_external(t_command *cmd, t_shell *shell);

int		backup_io(t_command *cmd, int *saved_stdin, int *saved_stdout);
int		redirect_io(t_command *cmd);
int		restore_io(t_command *cmd, int saved_stdin, int saved_stdout);

char	*get_env(const char *key, t_shell *shell);
void	unset_env(const char *key, t_shell *shell);
void	set_env(const char *expr, t_shell *shell);

// Builtins
int		builtin_env(t_command *cmd, t_shell *shell);
int		builtin_unset(t_command *cmd, t_shell *shell);
int		builtin_export(t_command *cmd, t_shell *shell);
int		builtin_exit(t_command *cmd, t_shell *shell);
int		builtin_echo(t_command *cmd, t_shell *shell);
int		builtin_pwd(t_command *cmd, t_shell *shell);
int		builtin_cd(t_command *cmd, t_shell *shell);

#endif
