/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:50 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/01 00:23:52 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "exec.h"
#include "parse.h"
#include "sig.h"

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

/*
Description: allocating memory for the shell struct. Copying the env into shell->envs
*/
t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_xmalloc(sizeof(*shell));
	shell->envs = ft_xstrdupv(envp);
	shell->exit_status = 0;
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &shell->term);
	return (shell);
}

void	free_shell(t_shell *shell)
{
	ft_strfreev(shell->envs);
	close(shell->stdin);
	close(shell->stdout);
	free(shell);
}

void	interactive_mode(t_shell *shell)
{
	char		*line;
	t_token		*token_list;
	t_command	*cmd_list;

	setup_signal_handlers();
	setup_readline();
    while (1)
    {
        line = readline("(minishell) ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		add_history(line);
		token_list = get_token(line, shell);
		if (token_list == NULL)
		{
			free(line);
			continue ;
		}
		//print_token_list(token_list);
		cmd_list = parsing_tokens(token_list);
		if (cmd_list == NULL)
		{
			free(line);
			free_token_list(token_list);
			continue ;
		}
		free(line);
		free_token_list(token_list);
		//print_cmd_list(cmd_list);
		exec_command(cmd_list, shell);
		free_cmd_list(cmd_list);
    }
	clear_history();
}

void	non_interactive_mode(t_shell *shell)
{
	char		*line;
	size_t		line_len;
	t_token		*token_list;
	t_command	*cmd_list;

	line = NULL;
	line_len = 0;
    while (getline(&line, &line_len, stdin) != -1)
    {
		// temporary hack for minishell_tester
		//puts("(minishell) ");
		token_list = get_token(line, shell);
		if (token_list == NULL)
		{
			continue ;
		}
		//print_token_list(token_list);
		cmd_list = parsing_tokens(token_list);
		if (cmd_list == NULL)
		{
			free_token_list(token_list);
			continue ;
		}
		free_token_list(token_list);
		//print_cmd_list(cmd_list);
		exec_command(cmd_list, shell);
		free_cmd_list(cmd_list);
    }
	free(line);
}

// TODO(ismail): Consider adding non-interactive mode with "-c" like BASH
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		last_exit_status;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (isatty(STDIN_FILENO))
	{
		interactive_mode(shell);
	}
	else
	{
		non_interactive_mode(shell);
	}
	last_exit_status = shell->exit_status;
	free_shell(shell);
    return (last_exit_status);
}
