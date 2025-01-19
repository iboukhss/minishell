/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:32:26 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/19 13:29:06 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*

Description: Interrate over the token list to build cmd structs.
A cmd struct corresponds to one or multiple consecutive tokens limited by a pipe or end of the token_list.
Multiple cmd form the cmd_list.

typedef struct s_command
{
	char		**args;			// Command and arguments
	bool		is_builtin;		// Flag for builtins (echo, cd, pwd, ect.)
	char		*infile;		// Input redirection file (<)
	char		*outfile;		// Output redirection file (>)
	bool		append_mode;	// Flag for append mode (>>)
	char		*heredoc;		// Heredoc delimiter (<<)
	t_command	*next;			// Pointer to next command in the pipeline (|)
}	t_command;

example : cat file.txt | grep "test" > output.txt
	if token->type = 'w' then token->content to args
	if token->type = '<' then (token->next)->content to infile
	if token->type = '>' then (token->next)->content to outfile
	if token->type = '-' then append_mode = TRUE and (token->next)->content to outfile
	if token->type = '+' then handle heredoc deliminter
	if token->type = '|' then current cmd is complete, create next cmd node and point to these one

The workflow involves tokenizing → parsing → validating → executing.
*/


/*
Description: Check if a token->content corresponds to a builtin command.
*/
int is_builtin(t_token *token)
{
	const char	*builtin_cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	const char	**builtin_cmd_ptr;
	size_t		len_token;

	builtin_cmd_ptr = builtin_cmd;
	len_token = ft_strlen(token->content);
	while (*builtin_cmd_ptr != NULL)
	{
		if (ft_strncmp(token->content, *builtin_cmd_ptr, len_token) == 0 &&
				ft_strlen(*builtin_cmd_ptr) == len_token)
				{
					return (1);
				}
		builtin_cmd_ptr++;
	}
	return (0);
}

/*
Description: Adding token->content to cmd->args
*/
int	add_arg(t_command *cmd, t_token *token)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL && i < MAX_ARGS)
		i++;
	if (i == MAX_ARGS)
		return (0);
	cmd->args[i] = ft_xstrdup(token->content);
	return (1);
}

/*
Description: Building the command node that is limited by the pipe or end of line.
*/
int	build_cmd(t_token *token, t_command *cmd)
{
	if (cmd->args[0] == NULL && is_builtin(token) == 1)
	{
		cmd->is_builtin = 1;
	}
	if (token->type == 'w' && cmd->append_mode == 0 && cmd->heredoc == NULL &&
			cmd->infile == NULL && cmd->outfile == NULL && add_arg(cmd, token) == 0)
	{
		return (0);
	}
	else if (token->type == '<')
	{
		cmd->infile = ft_xstrdup((token->next)->content);
	}
	else if (token->type == '>')
	{
		if (token->next == NULL)
			return (0);
		cmd->outfile = ft_xstrdup((token->next)->content);
	}
	else if (token->type == '-')
	{
		if (token->next == NULL)
			return (0);
		cmd->append_mode = 1;
		cmd->outfile = ft_xstrdup((token->next)->content);
	}
	else if (token->type == '+')
	{
		if (token->next == NULL)
			return (0);
		cmd->heredoc = ft_xstrdup((token->next)->content);
	}
	return (1);
}

t_command *parsing_tokens(t_token *token_list)
{
	t_command	*cmd_list;
	t_command	*cmd;
	t_token		*token;
	int			status;

	token = token_list;
	cmd = NULL;
	cmd_list = NULL;
	status = 0;
	while (token != NULL)
	{
		cmd = init_cmd();
		while (token != NULL && token->type != '|')
		{
			status = build_cmd(token, cmd);
			if (status == 0)
			{
				free_cmd_list(cmd_list);
				return (NULL);
			}
			if (token != NULL)
				token = token->next;
		}
		add_back_cmd(&cmd_list, cmd);
		if (token != NULL && token->type == '|')
			token = token->next;
	}
	return (cmd_list);
}
