/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:26 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/11 16:37:21 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void print_token_list(t_token *token_list)
{
	t_token	*current;

	if (token_list == NULL)
	{
		return ;
	}
	current = token_list;	
	while (current != NULL)
	{
		printf("content = %s, type : %c\n",current->content, current->type);
		current = current->next;
	}
}

void print_cmd_list(t_command *cmd_list)
{
	t_command	*current;
	size_t		i;
	int			node_count;

	node_count = 0;
	if (cmd_list == NULL)
	{
		return ;
	}
	current = cmd_list;	
	while (current != NULL)
	{
		i = 0;
		printf("Cmd node %d\n", node_count);
		printf("Cmd node address : %p\n", current);
		printf("Args : ");
		// NOTE(ismail): dirty patch to clearly show empty commands
		if (current->args[0] == NULL) printf("(null)");
		while (current->args[i] != NULL)
		{
			if (i != 0)
				printf(", ");
			printf("%s ", current->args[i]);
			i++;
		}
		printf("\n");
		printf("Infile : %s\n", current->infile);
		printf("Outfile : %s\n", current->outfile);
		printf("Heredoc : %s\n", current->heredoc);
		printf("Append_mode : %d\n", current->append_mode);
		printf("Builtin : %d\n", current->is_builtin);
		printf("Next cmd address : %p\n", current->next);
		printf("\n");
		node_count++;
		current = current->next;
	}	
}
