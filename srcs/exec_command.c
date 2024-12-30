/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:53 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/30 06:18:48 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// NOTE(ismail): Assuming this function is always called from a child process?
// This is probably bad.
static char	*resolve_path(const char *cmd_name, t_shell *shell)
{
	char	*path_var;
	char	*cmd_path;
	char	*dir_name;
	char	*beg, *end;

	if (access(cmd_name, X_OK) == 0)
	{
		return (ft_xstrdup(cmd_name));
	}
	path_var = get_env("PATH", shell);
	if (path_var == NULL)
	{
		fprintf(stderr, "PATH variable not set\n");
		exit(EXIT_FAILURE);
	}
	beg = path_var;
	end = beg;
	while (*end != '\0')
	{
		end = ft_strchrnul(beg, ':');
		// Skip empty tokens
		if (end - beg > 0)
		{
			dir_name = strndup(beg, end - beg);
			asprintf(&cmd_path, "%s/%s", dir_name, cmd_name);
			free(dir_name);
			if (access(cmd_path, X_OK) == 0)
			{
				return (cmd_path);
			}
			free(cmd_path);
		}
		beg = end + 1;
	}
	fprintf(stderr, "%s: command not found\n", cmd_name);
	exit(127);
}

int	exec_builtin(t_command *cmd, t_shell *shell)
{
	if (strcmp(cmd->args[0], "env") == 0)
	{
		builtin_env(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "unset") == 0)
	{
		builtin_unset(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "export") == 0)
	{
		builtin_export(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "exit") == 0)
	{
		builtin_exit(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "echo") == 0)
	{
		builtin_echo(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "pwd") == 0)
	{
		builtin_pwd(cmd, shell);
	}
	else if (strcmp(cmd->args[0], "cd") == 0)
	{
		builtin_cd(cmd, shell);
	}
	// TODO(ismail): Change this.
	return (0);
}

// TODO(ismail): Find a way to make the exit status propagate more reliably.
int	exec_external(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*bin_path;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		bin_path = resolve_path(cmd->args[0], shell);
		execve(bin_path, cmd->args, shell->envs);
		perror(cmd->args[0]);
		free(bin_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			return (128 + WTERMSIG(status));
		}
		return (1);
	}
}

void	exec_command(t_command *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	backup_io(cmd, &saved_stdin, &saved_stdout);
	if (redirect_io(cmd) == -1)
	{
		restore_io(cmd, saved_stdin, saved_stdout);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	if (cmd->is_builtin)
	{
		shell->exit_status = exec_builtin(cmd, shell);
	}
	else
	{
		shell->exit_status = exec_external(cmd, shell);
	}
	restore_io(cmd, saved_stdin, saved_stdout);
}
