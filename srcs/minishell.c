/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/12 12:53:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "libft.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// TODO(ismail): Consider adding non-interactive mode with "-c" like BASH
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*token_list;
	t_command	*cmd_list;
	t_shell		*shell;

	(void)argc;
	(void)argv;
	token_list = NULL;
	cmd_list = NULL;
	shell = init_shell(envp);
	while (1)
	{

		line = readline("(minishell) ");
		if (line == NULL)
		{
			continue ;
		}
		add_history(line);
		token_list = get_token(line, shell);
		if (token_list == NULL)
		{
			free(line);
			continue ;
		}
		free(line);
		line = NULL;
		cmd_list = parsing_tokens(token_list);
		if (cmd_list == NULL)
		{
			free(token_list);
			free(line);
			continue ;
		}
		//print_cmd_list(cmd_list);
		exec_command(cmd_list, shell);
		free_all(line, token_list, cmd_list);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}
