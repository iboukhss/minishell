/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:53 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:07:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "exec.h"

#include "libft.h"
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Find the full command path for a binary.
 * Needs improvement.
 */
int	find_command(char **cmd_path, const char *cmd_name, t_shell *shell)
{
	char	*path_var;
	char	*dir_name;
	char	*beg, *end;

	if (access(cmd_name, X_OK) == 0)
	{
		*cmd_path = ft_xstrdup(cmd_name);
		return (MS_XSUCCESS);
	}
	path_var = get_env("PATH", shell);
	if (path_var == NULL)
	{
		log_error("PATH variable not set");
		return (MS_XNOTFOUND);
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
			asprintf(cmd_path, "%s/%s", dir_name, cmd_name);
			free(dir_name);
			if (access(*cmd_path, X_OK) == 0)
			{
				return (MS_XSUCCESS);
			}
			free(*cmd_path);
		}
		beg = end + 1;
	}
	log_error("minishell: command not found");
	return (MS_XNOTFOUND);
}

/*
 * Finds the proper shell builtin.
 */
int	exec_builtin(t_command *cmd, t_shell *shell)
{
	if (strcmp(cmd->args[0], "env") == 0)
	{
		return (builtin_env(cmd, shell));
	}
	else if (strcmp(cmd->args[0], "unset") == 0)
	{
		return (builtin_unset(cmd, shell));
	}
	else if (strcmp(cmd->args[0], "export") == 0)
	{
		return (builtin_export(cmd, shell));
	}
	else if (strcmp(cmd->args[0], "exit") == 0)
	{
		return (builtin_exit(cmd, shell));
	}
	else if (strcmp(cmd->args[0], "echo") == 0)
	{
		return (builtin_echo(cmd));
	}
	else if (strcmp(cmd->args[0], "pwd") == 0)
	{
		return (builtin_pwd(cmd));
	}
	else if (strcmp(cmd->args[0], "cd") == 0)
	{
		return (builtin_cd(cmd, shell));
	}
	return (MS_XFAILURE);
}

/*
 * Executes an external binary and returns the proper exit status.
 */
int	exec_external(t_command *cmd, t_shell *shell)
{
	char	*bin_path;
	int		err;

	err = find_command(&bin_path, cmd->args[0], shell);
	if (err)
	{
		return (err);
	}
	execve(bin_path, cmd->args, shell->envs);
	perror(cmd->args[0]);
	free(bin_path);
	return (MS_XFAILURE);
}

void exec_from_pipe(t_command *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			exit(MS_XFAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append_mode)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (fd == -1)
		{
			perror(cmd->outfile);
			exit(MS_XFAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmd->is_builtin)
	{
		exit(exec_builtin(cmd, shell));
	}
	else
	{
		exit(exec_external(cmd, shell));
	}
}

/*
 * Executes the pipeline.
 * Need to add redirections.
 * Exit status stuff is probably wrong.
 */
int	exec_pipeline(t_command *cmd, t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(MS_XFAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(MS_XFAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			exec_from_pipe(cmd, shell);
		}
		if (prev_fd != -1)
		{
			close(prev_fd);
		}
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
	{
		// waits for all child processes
	}
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	else
	{
		return (MS_XFAILURE);
	}
}

/*
 * Executes a simple command, which can be of two forms: a shell builtin
 * function or an external binary.
 */
int	exec_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (cmd->is_builtin)
	{
		return (exec_builtin(cmd, shell));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(MS_XFAILURE);
		}
		if (pid == 0)
		{
			exit(exec_external(cmd, shell));
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(MS_XFAILURE);
		}
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			return (128 + WTERMSIG(status));
		}
		else
		{
			return (MS_XFAILURE);
		}
	}
}

/*
 * Entrypoint function, checks whether the input is a pipeline or a simple
 * and branches accordingly.
 */
void	exec_command(t_command *cmd, t_shell *shell)
{
	int	err;

	err = redirect_io(cmd, shell);
	if (err)
	{
		restore_io(cmd, shell);
		shell->exit_status = err;
		return ;
	}
	if (cmd->next)
	{
		shell->exit_status = exec_pipeline(cmd, shell);
	}
	else
	{
		shell->exit_status = exec_simple_command(cmd, shell);
	}
	restore_io(cmd, shell);
}
