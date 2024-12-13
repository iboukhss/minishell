/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:53 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/13 14:07:39 by iboukhss         ###   ########.fr       */
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

static void	exit_shell(int status, t_shell *shell)
{
	shell->exit_status = status;
	exit(status);
}

static char	*get_env(const char *key, t_shell *shell)
{
	char	**envp;
	int		key_len;
	int		i;

	envp = shell->envs;
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (envp[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}

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
		exit_shell(EXIT_FAILURE, shell);
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
			if (asprintf(&cmd_path, "%s/%s", dir_name, cmd_name) == -1)
			{
				perror("asprintf");
				free(dir_name);
				return (NULL);
			}
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
	exit_shell(127, shell);
	return (NULL);
}

void	exec_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// Child process
	if (pid == 0)
	{
		cmd_path = resolve_path(cmd->args[0], shell);
		execve(cmd_path, cmd->args, shell->envs);
		perror("execve");
		free(cmd_path);
		exit_shell(EXIT_FAILURE, shell);
	}
	// Parent process
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			shell->exit_status = 1;
		}
		if (WIFEXITED(status))
		{
			shell->exit_status = WEXITSTATUS(status);
		}
		else
		{
			shell->exit_status = 1;
		}
	}
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_command	cmd = {argv + 1, 0, NULL, NULL, 0, NULL, NULL};
	t_shell		shell = {envp, 0};

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	exec_command(&cmd, &shell);
	return (0);
}
*/
