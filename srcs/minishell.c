/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:50 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/07 18:03:31 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "exec.h"
#include "parse.h"
#include "token.h"
#include "sig.h"
#include "free.h"

#include "libft.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_input_interactive(char *line, t_token **token_list,
	t_command **cmd_list, t_shell **shell)
{
	if (line == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (-1);
	}
	add_history(line);
	*token_list = get_token(line, *shell);
	if (*token_list == NULL)
	{
		free(line);
		return (1);
	}
	*cmd_list = parsing_tokens(*token_list, *shell);
	free_token_list(*token_list);
	if (*cmd_list == NULL)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	interactive_mode(t_shell *shell)
{
	int			status;
	char		*line;
	t_token		*token_list;
	t_command	*cmd_list;

	setup_signal_handlers();
	setup_readline();
	while (1)
	{
		line = readline("(minishell) ");
		status = handle_input_interactive(line, &token_list, &cmd_list, &shell);
		if (status == -1)
			break ;
		else if (status == 1)
			continue ;
		free(line);
		exec_command(cmd_list, shell);
		free_cmd_list(cmd_list);
	}
	rl_clear_history();
}

int	handle_input_non_interactive(char *line, t_token **token_list,
	t_command **cmd_list, t_shell **shell)
{
	if (line == NULL)
		return (-1);
	*token_list = get_token(line, *shell);
	if (*token_list == NULL)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		return (1);
	}
	*cmd_list = parsing_tokens(*token_list, *shell);
	free_token_list(*token_list);
	if (*cmd_list == NULL)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		return (1);
	}
	return (0);
}

void	non_interactive_mode(t_shell *shell)
{
	char		*line;
	int			status;
	t_token		*token_list;
	t_command	*cmd_list;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		status = handle_input_non_interactive(line, &token_list,
				&cmd_list, &shell);
		if (status == -1)
			break ;
		else if (status == 1)
		
			continue ;
		exec_command(cmd_list, shell);
		free_cmd_list(cmd_list);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
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
